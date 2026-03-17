/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: martinmust <martinmust@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/24 23:59:25 by martinmust        #+#    #+#             */
/*   Updated: 2026/03/17 19:48:14 by martinmust       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	builtin_cd(t_data *data, t_cmd_set *cmd_set)
{
	char	*path;
	int		index;

	path = NULL;
	index = 0;
	if (!cmd_set)
		return (1);
	if (cmd_set->args && cmd_set->args[1])
	{
		printf("cd: too many arguments\n");
		return (1);
	}
	if (cmd_set->args && cmd_set->args[0])
		path = cmd_set->args[0];
	else
	{
		index = envp_index(data, "HOME");
		if (index == -1)
		{
			printf("cd: HOME not set\n");
			return (1);
		}
		path = ft_strchr(data->envp[index], '=');
		if (!path || path[1] == '\0')
		{
			printf("cd: HOME not set\n");
			return (1);
		}
		path++;
	}
	if (path == NULL)
	{
		printf("cd: HOME not set\n");
		return (1);
	}
	if (chdir(path) != 0)
	{
		perror("cd");
		return (1);
	}
	return (0);
}
