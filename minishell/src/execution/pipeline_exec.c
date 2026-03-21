/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline_exec.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: martinmust <martinmust@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/16 20:54:48 by martinmust        #+#    #+#             */
/*   Updated: 2026/03/21 19:23:48 by martinmust       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	update_parent_after_fork(t_exec_state *state, t_cmd_set *step)
{
	if (state->prev_fd != -1)
		close(state->prev_fd);
	if (step->fd_in != -1)
	{
		close(step->fd_in);
		step->fd_in = -1;
	}
	if (step->next)
		state->prev_fd = state->fd[0];
	else
		state->prev_fd = -1;
	if (step->next)
		close(state->fd[1]);
}

static void	wait_pipeline_children(t_exec_state *state)
{
	while (1)
	{
		state->waited_pid = wait(&state->status);
		if (state->waited_pid < 0)
			break ;
		if (state->waited_pid == state->last_pid)
			state->last_status = state->status;
	}
}

static void	init_exec_state(t_exec_state *state)
{
	state->last_status = 0;
	state->last_pid = -1;
	state->prev_fd = -1;
	state->status = 0;
}

static int	run_pipeline_steps(t_cmd_set *step, t_exec_state *state,
		t_data *data)
{
	while (step)
	{
		if (step->next)
		{
			if (pipe(state->fd) < 0)
			{
				perror("pipe");
				return (-1);
			}
		}
		state->pid = fork();
		if (state->pid < 0)
		{
			perror("fork");
			return (-1);
		}
		state->last_pid = state->pid;
		if (state->pid == 0)
			run_pipeline_child(state, step, data);
		update_parent_after_fork(state, step);
		step = step->next;
	}
	return (0);
}

int	execute_pipeline(t_data *data)
{
	t_cmd_set		*step;
	t_exec_state	state;

	step = data->t_pipeline;
	init_exec_state(&state);
	if (!step)
		return (0);
	if (prepare_heredocs(data->t_pipeline) != 0)
		return (-1);
	if (step->next == NULL && is_parent_builtin(step))
		return (run_parent_builtin(data, step));
	setup_wait_signals();
	if (run_pipeline_steps(step, &state, data) < 0)
		return (setup_signals(), -1);
	wait_pipeline_children(&state);
	setup_signals();
	if (WIFEXITED(state.last_status))
		data->exit_code = WEXITSTATUS(state.last_status);
	else if (WIFSIGNALED(state.last_status))
		data->exit_code = 128 + WTERMSIG(state.last_status);
	else
		data->exit_code = 1;
	return (0);
}
