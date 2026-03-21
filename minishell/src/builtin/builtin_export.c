/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: martinmust <martinmust@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/24 14:55:21 by steven            #+#    #+#             */
/*   Updated: 2026/03/21 21:44:50 by martinmust       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_valid_export_name(char *arg, int name_len)
{
	int	i;

	if (!arg || name_len <= 0)
		return (0);
	if (!ft_isalpha(arg[0]) && arg[0] != '_')
		return (0);
	i = 1;
	while (i < name_len)
	{
		if (!ft_isalnum(arg[i]) && arg[i] != '_')
			return (0);
		i++;
	}
	return (1);
}

static int	export_one_arg(t_data *data, char *arg)
{
	char	*equal_sign;
	int		name_len;

	equal_sign = ft_strchr(arg, '=');
	if (equal_sign)
		name_len = (int)(equal_sign - arg);
	else
		name_len = (int)ft_strlen(arg);
	if (!is_valid_export_name(arg, name_len))
	{
		fprintf(stderr, "export: invalid argument: %s\n", arg);
		return (1);
	}
	return (update_or_add_export_entry(data, arg, name_len,
			(equal_sign != NULL)));
}

int	builtin_export(t_data *data, t_cmd_set *cmd_set)
{
	int	i;
	int	status;

	if (!data || !cmd_set)
		return (1);
	if (!cmd_set->args || !cmd_set->args[0])
		return (builtin_env(data, cmd_set));
	if (!data->envp)
		return (1);
	i = 0;
	status = 0;
	while (cmd_set->args[i])
	{
		if (export_one_arg(data, cmd_set->args[i]) != 0)
			status = 1;
		i++;
	}
	return (status);
}
