/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: steven <steven@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/24 14:55:18 by steven            #+#    #+#             */
/*   Updated: 2026/02/27 18:37:37 by steven           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"




int builtin_env(t_data *data, t_cmd_set *cmd_set)
{
	int	i;

	if (!data || !cmd_set)
		return (1);
	if (cmd_set->args && cmd_set->args[0])
	{
		fprintf(stderr, "env cmd has too many arguments\n");
		return (1);
	}
	if (!data->envp)
		return (1);
	i = 0;
	while (data->envp[i])
	{
		printf("%s\n", data->envp[i]);
		i++;
	}
	return (0);
}
