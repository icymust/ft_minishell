/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: martinmust <martinmust@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/24 18:21:00 by steven            #+#    #+#             */
/*   Updated: 2026/03/08 12:54:01 by martinmust       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_cmd_set	*new_cmd_in_pl(t_data *data, t_cmd_set *current_set, char *name)
{
	if (!current_set)
	{
		current_set = new_cmd_set(CMD_SIMPLE, name);
		data->t_pipeline = current_set;
	}
	else
	{
		current_set->next = new_cmd_set(CMD_SIMPLE, name);
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
	printf("[DEBUG] Starting pipeline creation\n");
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
		token = token->next;
	}
	return (0);
}

int	execute_pipeline(t_data *data)
{
	t_cmd_set	*step;
	int			fd[2];
	pid_t		pid;
	int			prev_fd;
	int			status;

	status = 0;
	prev_fd = -1;
	step = data->t_pipeline;
	if (!step)
		printf("[DEBUG] No commands to execute in pipeline\n");
	while (step) {
		printf("[DEBUG PIPELINE] Command: %s\n", step->name);
		// print_cmd_set(step);

		// Создаём пайп, если есть следующая команда
		if (step->next)
			pipe(fd);

		pid = fork();
		if (pid == 0) {
			// Перенаправление stdin из предыдущего пайпа
			if (prev_fd != -1) {
				dup2(prev_fd, STDIN_FILENO);
				close(prev_fd);
			}
			// Перенаправление stdout в пайп
			if (step->next) {
				dup2(fd[1], STDOUT_FILENO);
				close(fd[1]);
				close(fd[0]);
			}
			// Редирект ввода из файла
			if (step->infile) {
				int fd_in = open(step->infile, O_RDONLY);
				if (fd_in < 0) {
					perror("minishell: infile");
					exit(1);
				}
				dup2(fd_in, STDIN_FILENO);
				close(fd_in);
			}
			// Редирект вывода в файл
			if (step->outfile) {
				int flags = O_WRONLY | O_CREAT | (step->out_append ? O_APPEND : O_TRUNC);
				int fd_out = open(step->outfile, flags, 0644);
				if (fd_out < 0) {
					perror("minishell: outfile");
					exit(1);
				}
				dup2(fd_out, STDOUT_FILENO);
				close(fd_out);
			}
			execute_cmd_set(step, data);
			exit(0);
		}
		// Родительский процесс
		if (prev_fd != -1)
			close(prev_fd);
		// Сохраняем read-end пайпа для следующей команды
		prev_fd = (step->next) ? fd[0] : -1;
		if (step->next)
			close(fd[1]);
		step = step->next;
	}

	// Ждём завершения всех дочерних процессов
	while (wait(&status) > 0);
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
