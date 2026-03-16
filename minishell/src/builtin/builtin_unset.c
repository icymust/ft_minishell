/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_unset.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: martinmust <martinmust@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/24 14:55:24 by steven            #+#    #+#             */
/*   Updated: 2026/03/17 01:53:26 by martinmust       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	unset_env_entry(t_data *data, int index)
{
	free(data->envp[index]);
	while (data->envp[index + 1])
	{
		data->envp[index] = data->envp[index + 1];
		index++;
	}
	data->envp[index] = NULL;
}

int	builtin_unset(t_data *data, t_cmd_set *cmd_set)
{
	int		index;
	int		i;
	int		name_len;
	int		status;

	i = 0;
	status = 0;
	if (!data || !cmd_set || !cmd_set->args)
		return (0);
	while (cmd_set->args[i])
	{
		name_len = (int)ft_strlen(cmd_set->args[i]);
		if (ft_strchr(cmd_set->args[i], '=')
			|| !is_valid_export_name(cmd_set->args[i], name_len))
		{
			fprintf(stderr, "unset: invalid identifier: %s\n", cmd_set->args[i]);
			status = 1;
			i++;
			continue ;
		}
		index = envp_index(data, cmd_set->args[i]);
		if (index < 0)
		{
			i++;
			continue ;
		}
		unset_env_entry(data, index);
		i++;
	}
	return (status);
}
