/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: martinmust <martinmust@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/24 14:55:21 by steven            #+#    #+#             */
/*   Updated: 2026/03/12 02:06:28 by martinmust       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_valid_export_name(char *arg, int name_len)
{
	int	i;

	if (!arg || name_len <= 0)
		return (0);
	// 1ABC=1 не должно проходить
	if (!ft_isalpha(arg[0]) && arg[0] != '_')
		return (0);
	i = 1;
	// ABC=1,_ABC=1 должно проходить
	while (i < name_len)
	{
		if (!ft_isalnum(arg[i]) && arg[i] != '_')
			return (0);
		i++;
	}
	return (1);
}

static int	envp_len(char **envp)
{
	int	i;

	i = 0;
	while (envp && envp[i])
		i++;
	return (i);
}

static int	append_env_entry(t_data *data, char *new_entry)
{
	char	**new_envp;
	int		len;
	int		i;

	len = envp_len(data->envp);
	new_envp = malloc(sizeof(char *) * (len + 2));
	if (!new_envp)
		return (1);
	i = 0;
	while (i < len)
	{
		new_envp[i] = data->envp[i];
		i++;
	}
	new_envp[len] = new_entry;
	new_envp[len + 1] = NULL;
	free(data->envp);
	data->envp = new_envp;
	return (0);
}

static int	export_one_arg(t_data *data, char *arg)
{
	char	*equal_sign;
	char	*name;
	char	*new_entry;
	int		name_len;
	int		index;

	equal_sign = ft_strchr(arg, '=');
	if (equal_sign)
		name_len = (int)(equal_sign - arg);
	else
		name_len = (int)ft_strlen(arg);
	if (!is_valid_export_name(arg, name_len))
		return (fprintf(stderr, "export: invalid argument: %s\n", arg), 1);
	name = ft_substr(arg, 0, name_len);
	if (!name)
		return (1);
	index = envp_index(data, name);
	free(name);
	if (!equal_sign)
	{
		if (index != -1)
			return (0);
		new_entry = ft_strjoin(arg, "=");
	}
	else
		new_entry = ft_strdup(arg);
	if (!new_entry)
		return (1);
	if (index != -1)
	{
		free(data->envp[index]);
		data->envp[index] = new_entry;
		return (0);
	}
	if (append_env_entry(data, new_entry) != 0)
	{
		free(new_entry);
		return (1);
	}
	return (0);
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
