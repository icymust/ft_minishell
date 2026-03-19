/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline_exec.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: martinmust <martinmust@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/16 20:54:48 by martinmust        #+#    #+#             */
/*   Updated: 2026/03/19 14:19:17 by martinmust       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "minishell.h"

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
		return (0);
	if (prepare_heredocs(data->t_pipeline) != 0)
		return (-1);
	if (step->next == NULL && is_parent_builtin(step))
		return (run_parent_builtin(data, step));
	setup_wait_signals();
	while (step)
	{
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
			signal(SIGINT, SIG_DFL);
			signal(SIGQUIT, SIG_DFL);
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
	setup_signals();
	if (WIFEXITED(last_status))
		data->exit_code = WEXITSTATUS(last_status);
	else if (WIFSIGNALED(last_status))
		data->exit_code = 128 + WTERMSIG(last_status);
	else
		data->exit_code = 1;
	return (0);
}
