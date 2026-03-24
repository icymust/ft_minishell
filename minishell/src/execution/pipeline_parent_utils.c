/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline_parent_utils.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: martinmust <martinmust@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/21 00:00:00 by martinmust        #+#    #+#             */
/*   Updated: 2026/03/25 00:07:35 by martinmust       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	set_pipeline_exit_code(t_data *data, int status)
{
	if (WIFEXITED(status))
		data->exit_code = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
		data->exit_code = 128 + WTERMSIG(status);
	else
		data->exit_code = 1;
}

int	is_parent_builtin(t_cmd_set *cmd_set)
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

int	save_parent_stdio(int *saved_stdio)
{
	saved_stdio[0] = -1;
	saved_stdio[1] = -1;
	saved_stdio[0] = dup(STDIN_FILENO);
	saved_stdio[1] = dup(STDOUT_FILENO);
	if (saved_stdio[0] >= 0 && saved_stdio[1] >= 0)
		return (0);
	perror("dup");
	if (saved_stdio[0] >= 0)
		close(saved_stdio[0]);
	if (saved_stdio[1] >= 0)
		close(saved_stdio[1]);
	return (-1);
}

void	restore_parent_stdio(int *saved_stdio)
{
	if (dup2(saved_stdio[0], STDIN_FILENO) < 0
		|| dup2(saved_stdio[1], STDOUT_FILENO) < 0)
		perror("dup");
	close(saved_stdio[0]);
	close(saved_stdio[1]);
}

int	wait_heredoc_child(pid_t pid, int *fd, t_cmd_set *cmd_set)
{
	int	status;

	close(fd[1]);
	setup_wait_signals();
	if (waitpid(pid, &status, 0) < 0)
	{
		setup_signals();
		close(fd[0]);
		perror("waitpid");
		return (1);
	}
	setup_signals();
	if (WIFSIGNALED(status) && WTERMSIG(status) == SIGINT)
	{
		write(1, "\n", 1);
		close(fd[0]);
		return (130);
	}
	if (!WIFEXITED(status) || WEXITSTATUS(status) != 0)
	{
		close(fd[0]);
		return (1);
	}
	cmd_set->fd_in = fd[0];
	return (0);
}
