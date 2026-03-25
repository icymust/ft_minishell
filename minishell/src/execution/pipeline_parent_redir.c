/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline_parent_redir.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: martinmust <martinmust@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/21 00:00:00 by martinmust        #+#    #+#             */
/*   Updated: 2026/03/21 00:00:00 by martinmust       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	parent_dup_error(int *saved_stdio, int fd)
{
	if (fd >= 0)
		close(fd);
	perror("dup2");
	restore_parent_stdio(saved_stdio);
	return (-1);
}

int	prepare_parent_input(t_data *data, t_cmd_set *cmd_set, int *saved_stdio)
{
	(void)data;
	if (cmd_set->fd_in != -1 && dup2(cmd_set->fd_in, STDIN_FILENO) < 0)
		return (parent_dup_error(saved_stdio, -1));
	if (cmd_set->fd_in != -1)
	{
		close(cmd_set->fd_in);
		cmd_set->fd_in = -1;
	}
	return (0);
}

int	prepare_parent_output(t_data *data, t_cmd_set *cmd_set, int *saved_stdio)
{
	if (apply_cmd_redirections(cmd_set) == 0)
		return (0);
	data->exit_code = 1;
	restore_parent_stdio(saved_stdio);
	return (1);
}
