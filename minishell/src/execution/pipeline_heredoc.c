/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline_heredoc.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: martinmust <martinmust@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/16 20:57:17 by martinmust        #+#    #+#             */
/*   Updated: 2026/03/25 00:07:12 by martinmust       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	setup_heredoc_child_signals(void)
{
	struct sigaction	sa;

	sa.sa_handler = SIG_DFL;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = 0;
	sigaction(SIGINT, &sa, NULL);
	sa.sa_handler = SIG_IGN;
	sigaction(SIGQUIT, &sa, NULL);
}

static int	is_heredoc_delim(char *line, char *delim)
{
	int	len;

	len = ft_strlen(delim);
	if (ft_strncmp(line, delim, len) != 0)
		return (0);
	return (line[len] == '\n' || line[len] == '\0');
}

static void	heredoc_child_process(int *fd, char *delim)
{
	char	*line;

	close(fd[0]);
	setup_heredoc_child_signals();
	while (1)
	{
		line = readline("heredoc> ");
		if (!line)
			break ;
		if (is_heredoc_delim(line, delim))
		{
			free(line);
			break ;
		}
		write(fd[1], line, ft_strlen(line));
		write(fd[1], "\n", 1);
		free(line);
	}
	close(fd[1]);
	exit(0);
}

static int	prepare_heredoc_for_cmd(t_cmd_set *cmd_set)
{
	int		fd[2];
	pid_t	pid;

	if (!cmd_set || !cmd_set->heredoc_delim)
		return (0);
	if (pipe(fd) < 0)
	{
		perror("pipe");
		return (1);
	}
	pid = fork();
	if (pid < 0)
	{
		close(fd[0]);
		close(fd[1]);
		perror("fork");
		return (1);
	}
	if (pid == 0)
		heredoc_child_process(fd, cmd_set->heredoc_delim);
	return (wait_heredoc_child(pid, fd, cmd_set));
}

int	prepare_heredocs(t_cmd_set *pipeline)
{
	t_cmd_set	*cmd_set;
	int			status;

	cmd_set = pipeline;
	while (cmd_set)
	{
		if (cmd_set->heredoc_delim)
		{
			status = prepare_heredoc_for_cmd(cmd_set);
			if (status != 0)
				return (status);
		}
		cmd_set = cmd_set->next;
	}
	return (0);
}
