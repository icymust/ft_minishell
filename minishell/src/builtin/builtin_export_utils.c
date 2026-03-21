/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: martinmust <martinmust@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/21 00:00:00 by martinmust        #+#    #+#             */
/*   Updated: 2026/03/21 00:00:00 by martinmust       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

static int	find_export_index(t_data *data, char *arg, int name_len)
{
	char	*name;
	int		index;

	name = ft_substr(arg, 0, name_len);
	if (!name)
		return (-2);
	index = envp_index(data, name);
	free(name);
	return (index);
}

static char	*build_export_entry(char *arg, int has_equal)
{
	if (has_equal)
		return (ft_strdup(arg));
	return (ft_strjoin(arg, "="));
}

int	update_or_add_export_entry(t_data *data, char *arg, int name_len,
		int has_equal)
{
	char	*new_entry;
	int		index;

	index = find_export_index(data, arg, name_len);
	if (index == -2)
		return (1);
	if (!has_equal && index != -1)
		return (0);
	new_entry = build_export_entry(arg, has_equal);
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
