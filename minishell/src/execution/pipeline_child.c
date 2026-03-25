/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline_child.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: martinmust <martinmust@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/21 18:19:42 by martinmust        #+#    #+#             */
/*   Updated: 2026/03/25 15:21:53 by martinmust       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
	if (apply_cmd_redirections(step) != 0)
		exit(1);
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	status = execute_cmd_set(step, data);
	exit(status);
}
