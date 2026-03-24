/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline_heredoc.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: martinmust <martinmust@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/16 20:57:17 by martinmust        #+#    #+#             */
/*   Updated: 2026/03/24 00:00:00 by martinmust       ###   ########.fr       */
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
		write(1, "heredoc> ", 9);
		line = get_next_line(STDIN_FILENO);
		if (!line)
			break ;
		if (is_heredoc_delim(line, delim))
		{
			free(line);
			break ;
		}
		write(fd[1], line, ft_strlen(line));
		free(line);
	}
	close(fd[1]);
	exit(0);
}

static int	wait_heredoc_child(pid_t pid, int *fd, t_cmd_set *cmd_set)
{
	int	status;

	close(fd[1]);
	setup_wait_signals();
	if (waitpid(pid, &status, 0) < 0)
		return (setup_signals(), close(fd[0]), perror("waitpid"), 1);
	setup_signals();
	if (WIFSIGNALED(status) && WTERMSIG(status) == SIGINT)
		return (write(1, "\n", 1), close(fd[0]), 130);
	if (!WIFEXITED(status) || WEXITSTATUS(status) != 0)
		return (close(fd[0]), 1);
	cmd_set->fd_in = fd[0];
	return (0);
}

static int	prepare_heredoc_for_cmd(t_cmd_set *cmd_set)
{
	int		fd[2];
	pid_t	pid;

	if (!cmd_set || !cmd_set->heredoc_delim)
		return (0);
	if (pipe(fd) < 0)
		return (perror("pipe"), 1);
	pid = fork();
	if (pid < 0)
		return (close(fd[0]), close(fd[1]), perror("fork"), 1);
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
