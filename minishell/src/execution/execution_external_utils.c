/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_external_utils.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: martinmust <martinmust@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/21 00:00:00 by martinmust        #+#    #+#             */
/*   Updated: 2026/03/21 00:00:00 by martinmust       ###   ########.fr       */
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

int	prepare_external_exec(t_data *data, t_cmd_set *cmd_set,
		char **cmd_path, char ***argv)
{
	if (ft_strchr(cmd_set->name, '/') && is_dir(cmd_set->name))
	{
		fprintf(stderr, "minishell: %s: Is a directory\n", cmd_set->name);
		return (126);
	}
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
