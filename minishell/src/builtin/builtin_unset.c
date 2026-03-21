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

static int	invalid_unset_arg(char *arg)
{
	int	name_len;

	name_len = (int)ft_strlen(arg);
	if (ft_strchr(arg, '=') || !is_valid_export_name(arg, name_len))
	{
		ft_putstr_fd("unset: invalid identifier: ", STDERR_FILENO);
		ft_putendl_fd(arg, STDERR_FILENO);
		return (1);
	}
	return (0);
}

static int	process_unset_arg(t_data *data, char *arg)
{
	int	index;

	if (invalid_unset_arg(arg))
		return (1);
	index = envp_index(data, arg);
	if (index < 0)
		return (0);
	unset_env_entry(data, index);
	return (0);
}

int	builtin_unset(t_data *data, t_cmd_set *cmd_set)
{
	int		i;
	int		status;

	if (!data || !cmd_set || !cmd_set->args)
		return (0);
	i = 0;
	status = 0;
	while (cmd_set->args[i])
	{
		if (process_unset_arg(data, cmd_set->args[i]) != 0)
			status = 1;
		i++;
	}
	return (status);
}
