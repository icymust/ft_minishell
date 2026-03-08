/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: martinmust <martinmust@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/27 16:52:51 by steven            #+#    #+#             */
/*   Updated: 2026/03/04 23:57:09 by martinmust       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_dir(char *name)
{
	struct stat	stats;

	if (stat(name, &stats) != 0)
		return (0);
	return (S_ISDIR(stats.st_mode));
}

static void	free_split(char **arr)
{
	int	i;

	if (!arr)
		return ;
	i = 0;
	while (arr[i])
	{
		free(arr[i]);
		i++;
	}
	free(arr);
}

static char	*resolve_direct_path(const char *name)
{
	char	*dup;

	if (!name || access(name, X_OK) != 0 || is_dir((char *)name))
		return (NULL);
	dup = ft_strdup(name);
	return (dup);
}

static char	*build_cmd(char **dirs, const char *name)
{
	char	*candidate;
	char	*cmd_env;
	int		i;

	i = 0;
	while (dirs[i])
	{
		candidate = ft_strjoin(dirs[i], "/");
		if (!candidate)
			return (NULL);
		cmd_env = ft_strjoin(candidate, name);
		free(candidate);
		if (!cmd_env)
			return (NULL);
		if (access(cmd_env, X_OK) == 0 && !is_dir(cmd_env))
			return (cmd_env);
		free(cmd_env);
		i++;
	}
	return (NULL);
}

char	*cmd_found(t_data *data, t_cmd_set *set)
{
	char	**dirs;
	char	*path_env;
	int		idx;
	char	*cmd_env;

	if (!data || !set || !set->name)
		return (NULL);
	if (ft_strchr(set->name, '/') != NULL)
		return (resolve_direct_path(set->name));
	idx = envp_index(data, "PATH");
	if (idx == -1 || !data->envp[idx])
		return (NULL);
	path_env = data->envp[idx];
	dirs = ft_split(path_env + 5, ':');
	if (!dirs)
		return (NULL);
	cmd_env = build_cmd(dirs, set->name);
	free_split(dirs);
	return (cmd_env);
}
