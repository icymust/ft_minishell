/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_redirections.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: martinmust <martinmust@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/25 01:00:00 by martinmust        #+#    #+#             */
/*   Updated: 2026/03/25 15:17:56 by martinmust       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	apply_input_redir(t_redir *redir)
{
	int	fd;

	fd = open(redir->file, O_RDONLY);
	if (fd < 0)
		return (perror(redir->file), 1);
	if (dup2(fd, STDIN_FILENO) < 0)
	{
		close(fd);
		return (perror("dup2"), 1);
	}
	close(fd);
	return (0);
}

static int	apply_output_redir(t_redir *redir)
{
	int	fd;
	int	flags;

	flags = O_WRONLY | O_CREAT;
	if (redir->type == LEX_APPEND)
		flags |= O_APPEND;
	else
		flags |= O_TRUNC;
	fd = open(redir->file, flags, 0644);
	if (fd < 0)
		return (perror(redir->file), 1);
	if (dup2(fd, STDOUT_FILENO) < 0)
	{
		close(fd);
		perror("dup2");
		return (1);
	}
	close(fd);
	return (0);
}

int	apply_cmd_redirections(t_cmd_set *cmd_set)
{
	t_redir	*redir;

	redir = cmd_set->redirs;
	while (redir)
	{
		if (redir->type == LEX_REDIRECT_IN && apply_input_redir(redir) != 0)
			return (1);
		if ((redir->type == LEX_REDIRECT_OUT || redir->type == LEX_APPEND)
			&& apply_output_redir(redir) != 0)
			return (1);
		redir = redir->next;
	}
	return (0);
}
