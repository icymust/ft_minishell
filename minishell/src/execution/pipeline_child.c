/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline_child.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: martinmust <martinmust@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/21 18:19:42 by martinmust        #+#    #+#             */
/*   Updated: 2026/03/21 18:23:22 by martinmust       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	get_output_flags(t_cmd_set *step)
{
	if (step->out_append)
		return (O_WRONLY | O_CREAT | O_APPEND);
	return (O_WRONLY | O_CREAT | O_TRUNC);
}

static void	apply_child_input_redirection(t_cmd_set *step)
{
	int	fd_in;

	if (!step->infile)
		return ;
	fd_in = open(step->infile, O_RDONLY);
	if (fd_in < 0)
	{
		perror("minishell: infile");
		exit(1);
	}
	dup2(fd_in, STDIN_FILENO);
	close(fd_in);
}

static void	apply_child_output_redirection(t_cmd_set *step)
{
	int	fd_out;
	int	flags;

	if (!step->outfile)
		return ;
	flags = get_output_flags(step);
	fd_out = open(step->outfile, flags, 0644);
	if (fd_out < 0)
	{
		perror("minishell: outfile");
		exit(1);
	}
	dup2(fd_out, STDOUT_FILENO);
	close(fd_out);
}

static void	apply_child_file_redirections(t_cmd_set *step)
{
	apply_child_input_redirection(step);
	apply_child_output_redirection(step);
}

void	run_pipeline_child(t_exec_state *state, t_cmd_set *step, t_data *data)
{
	int	status;

	if (state->prev_fd != -1)
		dup2(state->prev_fd, STDIN_FILENO);
	if (step->fd_in != -1)
		dup2(step->fd_in, STDIN_FILENO);
	if (step->next)
		dup2(state->fd[1], STDOUT_FILENO);
	if (state->prev_fd != -1)
		close(state->prev_fd);
	if (step->fd_in != -1)
		close(step->fd_in);
	if (step->next)
	{
		close(state->fd[1]);
		close(state->fd[0]);
	}
	apply_child_file_redirections(step);
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	status = execute_cmd_set(step, data);
	exit(status);
}
