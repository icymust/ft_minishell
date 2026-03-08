/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: martinmust <martinmust@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/24 23:59:25 by martinmust        #+#    #+#             */
/*   Updated: 2026/03/02 20:19:12 by martinmust       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	builtin_cd(t_cmd_set *cmd_set)
{
	char	*path;

	path = NULL;
	if (!cmd_set)
		return ;
	if (cmd_set->args && cmd_set->args[1])
	{
		printf("cd: too many arguments\n");
		return ;
	}
	if (cmd_set->args && cmd_set->args[0])
		path = cmd_set->args[0];
	else
		path = getenv("HOME");
	if (path == NULL)
	{
		write(2, "cd: HOME not set\n", 17);
		return ;
	}
	if (chdir(path) != 0)
		perror("cd");
}
