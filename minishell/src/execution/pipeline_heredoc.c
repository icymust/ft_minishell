/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline_heredoc.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: martinmust <martinmust@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/16 20:57:17 by martinmust        #+#    #+#             */
/*   Updated: 2026/03/16 21:00:56 by martinmust       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "minishell.h"

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

int	prepare_heredocs(t_cmd_set *pipeline)
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
