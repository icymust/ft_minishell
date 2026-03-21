/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: martinmust <martinmust@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/23 19:50:22 by martinmust        #+#    #+#             */
/*   Updated: 2026/03/21 21:26:06 by martinmust       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	run_external_child(t_data *data, char *cmd_path, char **argv)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	if (execve(cmd_path, argv, data->envp) < 0)
	{
		perror("Execution failed");
		free(cmd_path);
		free(argv);
		exit(127);
	}
}

static int	wait_external_child(pid_t pid)
{
	int	status;

	if (waitpid(pid, &status, 0) < 0)
	{
		perror("waitpid");
		return (-1);
	}
	if (WIFSIGNALED(status))
		return (128 + WTERMSIG(status));
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	return (0);
}

int	execute_external_command(t_data *data, t_cmd_set *cmd_set)
{
	char	**argv;
	char	*cmd_path;
	pid_t	pid;
	int		status;

	status = prepare_external_exec(data, cmd_set, &cmd_path, &argv);
	if (status != 0)
		return (status);
	pid = fork();
	if (pid < 0)
	{
		free(cmd_path);
		free(argv);
		return (perror("fork"), -1);
	}
	if (pid == 0)
		run_external_child(data, cmd_path, argv);
	status = wait_external_child(pid);
	free(argv);
	free(cmd_path);
	return (status);
}

int	execute_cmd_set(t_cmd_set *cmd_set, t_data *data)
{
	int	status;

	if (!cmd_set || !data)
		return (1);
	if (is_builtin(cmd_set))
		status = execute_builtin(data, cmd_set);
	else
		status = execute_external_command(data, cmd_set);
	if (status < 0)
	{
		data->exit_code = 1;
		return (1);
	}
	else
	{
		data->exit_code = status;
		return (status);
	}
}
