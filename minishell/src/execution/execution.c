/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: martinmust <martinmust@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/23 19:50:22 by martinmust        #+#    #+#             */
/*   Updated: 2026/03/06 00:48:12 by martinmust       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	**build_exec_argv(t_cmd_set *cmd_set)
{
	char	**argv;
	int		i;
	int		count;

	if (!cmd_set || !cmd_set->name)
		return (NULL);
	count = 0;
	while (cmd_set->args && cmd_set->args[count])
		count++;
	argv = malloc(sizeof(char *) * (count + 2));
	if (!argv)
		return (NULL);
	argv[0] = cmd_set->name;
	i = 0;
	while (i < count)
	{
		argv[i + 1] = cmd_set->args[i];
		i++;
	}
	argv[count + 1] = NULL;
	return (argv);
}

int	execute_external_command(t_data *data, t_cmd_set *cmd_set)
{
	char	**argv;
	char	*cmd_path;
	pid_t	pid;
	int		status;

	printf("[DEBUG] Executing external command: %s\n", cmd_set->name);
	cmd_path = cmd_found(data, cmd_set);
	if (!cmd_path)
	{
		fprintf(stderr, "Command not found: %s\n", cmd_set->name);
		return (127);
	}
	argv = build_exec_argv(cmd_set);
	if (!argv)
	{
		free(cmd_path);
		return (perror("malloc"), -1);
	}
	pid = fork();
	if (pid < 0)
	{
		free(cmd_path);
		free(argv);
		return (perror("fork"), -1);
	}
	else if (pid == 0)
	{
		if (execve(cmd_path, argv, data->envp) < 0)
		{
			perror("Execution failed");
			free(cmd_path);
			free(argv);
			exit(127);
		}
	}
	else if (waitpid(pid, &status, 0) < 0)
	{
		free(argv);
		free(cmd_path);
		perror("waitpid");
		return (-1);
	}
	free(argv);
	free(cmd_path);
	if (WIFSIGNALED(status))
		return (128 + WTERMSIG(status));
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	return (0);
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
	data->exit_code = status;
	return (0);
}
