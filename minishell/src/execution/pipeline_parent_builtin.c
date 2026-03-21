/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline_parent_builtin.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: martinmust <martinmust@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/16 21:03:40 by martinmust        #+#    #+#             */
/*   Updated: 2026/03/21 00:00:00 by martinmust       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	run_parent_builtin(t_data *data, t_cmd_set *cmd_set)
{
	int	saved_stdio[2];
	int	status;

	if (!data || !cmd_set)
		return (1);
	if (save_parent_stdio(saved_stdio) < 0)
		return (-1);
	status = prepare_parent_input(data, cmd_set, saved_stdio);
	if (status != 0)
		return (status);
	status = prepare_parent_output(data, cmd_set, saved_stdio);
	if (status != 0)
		return (status);
	status = execute_builtin(data, cmd_set);
	data->exit_code = status;
	restore_parent_stdio(saved_stdio);
	return (status);
}
