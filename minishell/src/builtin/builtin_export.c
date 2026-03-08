/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: steven <steven@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/24 14:55:21 by steven            #+#    #+#             */
/*   Updated: 2026/02/27 14:37:26 by steven           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

#include "minishell.h"





int builtin_export(t_data *data, t_cmd_set *cmd_set)
{
	

	if (!data || !cmd_set)
		return (1);
	if (!cmd_set->args || !cmd_set->args[0])
	{
		builtin_env(data, cmd_set);
		return (1);
	}
	if (!data->envp)
		return (1);
	printf("[DEBUG] TODO Exporting to be implemented\n");
	return (0);
}