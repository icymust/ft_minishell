/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_set.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: martinmust <martinmust@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/25 10:20:36 by steven            #+#    #+#             */
/*   Updated: 2026/03/21 23:27:16 by martinmust       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_cmd_set(t_cmd_set *cmd_set)
{
	if (!cmd_set)
		return ;
	cmd_set->name = NULL;
	cmd_set->infile = NULL;
	cmd_set->outfile = NULL;
	cmd_set->heredoc_delim = NULL;
	cmd_set->args = NULL;
	cmd_set->out_append = 0;
	cmd_set->fd_in = -1;
	cmd_set->fd_out = -1;
	cmd_set->pid = -1;
	cmd_set->next = NULL;
}

t_cmd_set	*new_cmd_set(char *name)
{
	t_cmd_set	*cmd_set;

	cmd_set = NULL;
	cmd_set = malloc(sizeof(t_cmd_set));
	if (!cmd_set)
		return (NULL);
	init_cmd_set(cmd_set);
	if (name)
		cmd_set->name = ft_strdup(name);
	else
		cmd_set->name = NULL;
	cmd_set->args = NULL;
	cmd_set->next = NULL;
	return (cmd_set);
}

t_cmd_set	*new_cmd_in_pl(t_data *data, t_cmd_set *current_set, char *name)
{
	if (!current_set)
	{
		current_set = new_cmd_set(name);
		data->t_pipeline = current_set;
	}
	else
	{
		current_set->next = new_cmd_set(name);
		current_set = current_set->next;
	}
	return (current_set);
}

int	add_arg_to_cmd_set(t_cmd_set *cmd_set, char *arg)
{
	char	**new_args;
	int		i;

	if (!cmd_set || !arg)
		return (1);
	i = 0;
	while (cmd_set->args && cmd_set->args[i])
		i++;
	new_args = malloc(sizeof(char *) * (i + 2));
	if (!new_args)
		return (1);
	i = 0;
	while (cmd_set->args && cmd_set->args[i])
	{
		new_args[i] = cmd_set->args[i];
		i++;
	}
	new_args[i] = ft_strdup(arg);
	new_args[i + 1] = NULL;
	free(cmd_set->args);
	cmd_set->args = new_args;
	return (0);
}

void	free_cmd_set(t_cmd_set *cmd_set)
{
	int	i;

	i = 0;
	if (!cmd_set)
		return ;
	free(cmd_set->name);
	free(cmd_set->infile);
	free(cmd_set->outfile);
	free(cmd_set->heredoc_delim);
	if (cmd_set->fd_in != -1)
		close(cmd_set->fd_in);
	if (cmd_set->fd_out != -1)
		close(cmd_set->fd_out);
	if (cmd_set->args)
	{
		while (cmd_set->args[i])
			free(cmd_set->args[i++]);
		free(cmd_set->args);
	}
	free(cmd_set);
}
