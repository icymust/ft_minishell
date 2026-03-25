/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_external_utils.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: martinmust <martinmust@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/21 00:00:00 by martinmust        #+#    #+#             */
/*   Updated: 2026/03/25 15:20:11 by martinmust       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	**build_exec_argv(t_cmd_set *cmd_set)
{
	char	**argv;
	int		count;
	int		i;

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

static int	prepare_direct_path(char *name, char **cmd_path)
{
	if (!ft_strchr(name, '/'))
		return (0);
	if (is_dir(name))
	{
		fprintf(stderr, "minishell: %s: Is a directory\n", name);
		return (126);
	}
	if (access(name, F_OK) != 0)
	{
		perror(name);
		return (127);
	}
	if (access(name, X_OK) != 0)
	{
		perror(name);
		return (126);
	}
	*cmd_path = ft_strdup(name);
	if (!*cmd_path)
	{
		perror("malloc");
		return (-1);
	}
	return (1);
}

int	prepare_external_exec(t_data *data, t_cmd_set *cmd_set, char **cmd_path,
		char ***argv)
{
	int	status;

	status = prepare_direct_path(cmd_set->name, cmd_path);
	if (status < 0 || status == 126 || status == 127)
		return (status);
	if (status == 0)
		*cmd_path = cmd_found(data, cmd_set);
	if (!*cmd_path)
	{
		fprintf(stderr, "Command not found: %s\n", cmd_set->name);
		return (127);
	}
	*argv = build_exec_argv(cmd_set);
	if (!*argv)
	{
		free(*cmd_path);
		perror("malloc");
		return (-1);
	}
	return (0);
}
