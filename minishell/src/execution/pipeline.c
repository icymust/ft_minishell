/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: martinmust <martinmust@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/24 18:21:00 by steven            #+#    #+#             */
/*   Updated: 2026/03/16 17:30:09 by martinmust       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	prepare_heredoc_for_cmd(t_cmd_set *cmd_set)
{
	int		fd[2];
	char	*line;

	if (!cmd_set || !cmd_set->heredoc_delim)
		return (0);
	if (pipe(fd) < 0)
		return (perror("pipe"), 1);
	while (1)
	{
		line = readline("heredoc> ");
		if (!line)
			break ;
		if (ft_strncmp(line, cmd_set->heredoc_delim,
				ft_strlen(cmd_set->heredoc_delim) + 1) == 0)
		{
			free(line);
			break ;
		}
		write(fd[1], line, ft_strlen(line));
		write(fd[1], "\n", 1);
		free(line);
	}
	close(fd[1]);
	cmd_set->fd_in = fd[0];
	return (0);
}

static int	prepare_heredocs(t_cmd_set *pipeline)
{
	t_cmd_set	*cmd_set;

	cmd_set = pipeline;
	while (cmd_set)
	{
		if (cmd_set->heredoc_delim && prepare_heredoc_for_cmd(cmd_set) != 0)
			return (1);
		cmd_set = cmd_set->next;
	}
	return (0);
}

t_cmd_set	*new_cmd_in_pl(t_data *data, t_cmd_set *current_set, char *name)
{
	if (!current_set)
	{
		current_set = new_cmd_set(name);
		data->t_pipeline = current_set;
	}
	else
	{
		current_set->next = new_cmd_set(name);
		current_set = current_set->next;
	}
	return (current_set);
}

int	create_pipeline(t_data *data)
{
	t_token		*token;
	t_cmd_set	*current_set;

	if (!data)
		return (1);
	data->t_pipeline = NULL;
	current_set = NULL;
	if (!data->tokens)
	{
		printf("[DEBUG] No tokens found for pipeline creation\n");
		return (1);
	}
	token = data->tokens;
	while (token)
	{
		if (token->ast_type == LEX_REDIRECT_IN)
		{
			if (!current_set || !token->next)
				return (fprintf(stderr,
						"Syntax error: missing infile after '<'\n"), 1);
			add_redirect_in_to_cmd_set(data, current_set, token->next->value);
		}
		else if (token->ast_type == LEX_REDIRECT_OUT)
		{
			if (!current_set || !token->next)
				return (fprintf(stderr,
						"Syntax error: missing outfile after '>'\n"), 1);
			add_redirect_out_to_cmd_set(data, current_set, token->next->value);
		}
		else if (token->ast_type == LEX_APPEND)
		{
			if (!current_set || !token->next)
				return (fprintf(stderr,
						"Syntax error: missing outfile after '>>'\n"), 1);
			add_append_to_cmd_set(data, current_set, token->next->value);
		}
		if (token->ast_type == LEX_COMMAND)
		{
			current_set = new_cmd_in_pl(data, current_set, token->value);
			if (!current_set)
				return (1);
		}
		if (token->ast_type == LEX_ARGS)
		{
			if (!current_set)
				return (fprintf(stderr,
						"Syntax error: argument without command\n"), 1);
			add_arg_to_cmd_set(current_set, token->value);
		}
		if (token->ast_type == LEX_HEREDOC)
		{
			if (!current_set || !token->next
				|| token->next->ast_type != LEX_DELIMITER)
				return (fprintf(stderr, "Syntax error: heredoc\n"), 1);
			if (current_set->heredoc_delim)
				return (fprintf(stderr,
						"Syntax error: multiple heredoc delimiters for one command\n"),
					1);
			current_set->heredoc_delim = ft_strdup(token->next->value);
		}
		token = token->next;
	}
	return (0);
}

static int	is_parent_builtin(t_cmd_set *cmd_set)
{
	if (!cmd_set || !cmd_set->name)
		return (0);
	if (ft_strncmp(cmd_set->name, "cd", 2) == 0 && cmd_set->name[2] == '\0')
		return (1);
	if (ft_strncmp(cmd_set->name, "export", 6) == 0
		&& cmd_set->name[6] == '\0')
		return (1);
	if (ft_strncmp(cmd_set->name, "unset", 5) == 0
		&& cmd_set->name[5] == '\0')
		return (1);
	if (ft_strncmp(cmd_set->name, "exit", 4) == 0
		&& cmd_set->name[4] == '\0')
		return (1);
	return (0);
}

int run_parent_builtin(t_data *data, t_cmd_set *cmd_set){
	int saved_stdin;
	int saved_stdout;
	int fd_in;
	int status;

	if (!data || !cmd_set)
		return (1);
	saved_stdin = dup(STDIN_FILENO);
	saved_stdout = dup(STDOUT_FILENO);
	fd_in = -1;
	status = 0;
	if (saved_stdin < 0 || saved_stdout < 0)
		return (perror("dup"), -1);
	if (cmd_set->fd_in != -1)
	{
		if (dup2(cmd_set->fd_in, STDIN_FILENO) < 0)
		return (perror("dup2"), -1);
		close(cmd_set->fd_in);
		cmd_set->fd_in = -1;
	}
	if (cmd_set->infile)
	{
		fd_in = open(cmd_set->infile, O_RDONLY);
		if (fd_in < 0)
		{
			perror("minishell: infile");
			data->exit_code = 1;
			dup2(saved_stdin, STDIN_FILENO);
			dup2(saved_stdout, STDOUT_FILENO);
			close(saved_stdin);
			close(saved_stdout);
			return (1);
		}
		dup2(fd_in, STDIN_FILENO);
		close(fd_in);
	}
	if (cmd_set->outfile)
	{
		int flags = O_WRONLY | O_CREAT | (cmd_set->out_append ? O_APPEND : O_TRUNC);
		int fd_out = open(cmd_set->outfile, flags, 0644);
		if (fd_out < 0)
		{
			perror("minishell: outfile");
			data->exit_code = 1;
			if (dup2(saved_stdin, STDIN_FILENO) < 0 || dup2(saved_stdout, STDOUT_FILENO) < 0)
				perror("dup");
			close(saved_stdin);
			close(saved_stdout);
			return (1);
		}
		dup2(fd_out, STDOUT_FILENO);
		close(fd_out);
	}
	status = execute_builtin(data, cmd_set);
	data->exit_code = status;
	if (dup2(saved_stdin, STDIN_FILENO) < 0 || dup2(saved_stdout, STDOUT_FILENO) < 0)
		perror("dup");
	close(saved_stdin);
	close(saved_stdout);

	return(status);
}

int	execute_pipeline(t_data *data)
{
	t_cmd_set	*step;
	int			fd[2];
	pid_t		pid;
	pid_t		waited_pid;
	int			prev_fd;
	int			last_status;
	int			status;
	pid_t		last_pid;
	int			fd_in;
	int			flags;
	int			fd_out;

	status = 0;
	last_status = 0;
	last_pid = -1;
	prev_fd = -1;
	step = data->t_pipeline;
	if (!step)
		printf("[DEBUG] No commands to execute in pipeline\n");
	if (prepare_heredocs(data->t_pipeline) != 0)
		return (-1);
	while (step)
	{
		// printf("[DEBUG PIPELINE] Command: %s\n", step->name);
		// print_cmd_set(step);
		if (prev_fd == -1 && step->next == NULL && is_parent_builtin(step))
			return (run_parent_builtin(data, step));
		// Создаём пайп, если есть следующая команда
		if (step->next)
		{
			if (pipe(fd) < 0)
				return (perror("pipe"), -1);
		}
		pid = fork();
		if (pid < 0)
		{
			perror("fork");
			return (-1);
		}
		last_pid = pid;
		if (pid == 0)
		{
			// Перенаправление stdin из предыдущего пайпа
			if (prev_fd != -1)
			{
				dup2(prev_fd, STDIN_FILENO);
				close(prev_fd);
			}
			if (step->fd_in != -1)
			{
				dup2(step->fd_in, STDIN_FILENO);
				close(step->fd_in);
			}
			// Перенаправление stdout в пайп
			if (step->next)
			{
				dup2(fd[1], STDOUT_FILENO);
				close(fd[1]);
				close(fd[0]);
			}
			// Редирект ввода из файла
			if (step->infile)
			{
				fd_in = open(step->infile, O_RDONLY);
				if (fd_in < 0)
				{
					perror("minishell: infile");
					exit(1);
				}
				dup2(fd_in, STDIN_FILENO);
				close(fd_in);
			}
			// Редирект вывода в файл
			if (step->outfile)
			{
				flags = O_WRONLY | O_CREAT | (step->out_append ? O_APPEND : O_TRUNC);
				fd_out = open(step->outfile, flags, 0644);
				if (fd_out < 0)
				{
					perror("minishell: outfile");
					exit(1);
				}
				dup2(fd_out, STDOUT_FILENO);
				close(fd_out);
			}
			status = execute_cmd_set(step, data);
			exit(status);
		}
		// Родительский процесс
		if (prev_fd != -1)
			close(prev_fd);
		if (step->fd_in != -1)
		{
			close(step->fd_in);
			step->fd_in = -1;
		}
		// Сохраняем read-end пайпа для следующей команды
		prev_fd = (step->next) ? fd[0] : -1;
		if (step->next)
			close(fd[1]);
		step = step->next;
	}
	// Ждём завершения всех дочерних процессов
	while (1)
	{
		waited_pid = wait(&status);
		if (waited_pid < 0)
			break ;
		if (waited_pid == last_pid)
			last_status = status;
	}
	if (WIFEXITED(last_status))
		data->exit_code = WEXITSTATUS(last_status);
	else if (WIFSIGNALED(last_status))
		data->exit_code = 128 + WTERMSIG(last_status);
	else
		data->exit_code = 1;
	return (0);
}

void	free_pipeline(t_data *data)
{
	t_cmd_set	*temp;
	t_cmd_set	*pipeline;

	if (!data)
		return ;
	pipeline = data->t_pipeline;
	while (pipeline)
	{
		temp = pipeline;
		pipeline = pipeline->next;
		free_cmd_set(temp);
	}
	data->t_pipeline = NULL;
}
