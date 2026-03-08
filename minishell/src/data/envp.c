/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envp.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: steven <steven@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/25 13:01:22 by steven            #+#    #+#             */
/*   Updated: 2026/02/27 18:37:44 by steven           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	envp_index(t_data *data, char *var_name)
{
	int i;
	int		index;
	char	*name_egal;
	char	**envp;
	
	if (!data || !var_name)
		return (-1);
	envp = data->envp;
	name_egal = ft_strjoin(var_name, "=");
	if (!name_egal)
		return (-1);
	index = -1;
	i = 0;
	while (envp[i])
	{
		if (ft_strncmp(name_egal, envp[i], ft_strlen(name_egal)) == 0)
		{
			index = i;
			break;
		}
		i++;
	}
	free(name_egal);
	return (index);
}

char **copy_env(char **env)
{
    int i;
    char **dest;
    if (!env)
        return (NULL);
    i = 0;
    while (env[i])
        i++;
    dest = malloc(sizeof(char *) * (i + 1));
    if (!dest)
        return (NULL);
    i = 0;
    while (env[i])
    {
        dest[i] = ft_strdup(env[i]);
        i++;
    }
    dest[i] = NULL;
    return (dest);
}