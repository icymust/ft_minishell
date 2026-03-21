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

static int	parent_open_error(t_data *data, int *saved_stdio, char *message)
{
	perror(message);
	data->exit_code = 1;
	restore_parent_stdio(saved_stdio);
	return (1);
}

int	prepare_parent_input(t_data *data, t_cmd_set *cmd_set, int *saved_stdio)
{
	int	fd_in;

	if (cmd_set->fd_in != -1 && dup2(cmd_set->fd_in, STDIN_FILENO) < 0)
		return (parent_dup_error(saved_stdio, -1));
	if (cmd_set->fd_in != -1)
	{
		close(cmd_set->fd_in);
		cmd_set->fd_in = -1;
	}
	if (!cmd_set->infile)
		return (0);
	fd_in = open(cmd_set->infile, O_RDONLY);
	if (fd_in < 0)
		return (parent_open_error(data, saved_stdio, "minishell: infile"));
	if (dup2(fd_in, STDIN_FILENO) < 0)
		return (parent_dup_error(saved_stdio, fd_in));
	close(fd_in);
	return (0);
}

int	prepare_parent_output(t_data *data, t_cmd_set *cmd_set, int *saved_stdio)
{
	int	fd_out;
	int	flags;

	if (!cmd_set->outfile)
		return (0);
	flags = O_WRONLY | O_CREAT;
	if (cmd_set->out_append)
		flags |= O_APPEND;
	else
		flags |= O_TRUNC;
	fd_out = open(cmd_set->outfile, flags, 0644);
	if (fd_out < 0)
		return (parent_open_error(data, saved_stdio, "minishell: outfile"));
	if (dup2(fd_out, STDOUT_FILENO) < 0)
		return (parent_dup_error(saved_stdio, fd_out));
	close(fd_out);
	return (0);
}
