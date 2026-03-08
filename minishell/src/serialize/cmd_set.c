/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_set.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: steven <steven@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/25 10:20:36 by steven            #+#    #+#             */
/*   Updated: 2026/02/27 10:10:58 by steven           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void init_cmd_set(t_cmd_set *cmd_set)
{
    if (!cmd_set)
        return;
    cmd_set->type = CMD_SIMPLE;
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

t_cmd_set *new_cmd_set(t_cmd_type type, char *name)
{
    t_cmd_set *cmd_set;

    cmd_set = NULL;
    cmd_set = malloc(sizeof(t_cmd_set));
    if (!cmd_set)
        return (NULL);
    init_cmd_set(cmd_set);
    cmd_set->type = type;
    if (name)
        cmd_set->name = ft_strdup(name);
    else
        cmd_set->name = NULL;
    cmd_set->args = NULL;
    cmd_set->next = NULL;
    return (cmd_set);
}

int add_arg_to_cmd_set(t_cmd_set *cmd_set, char *arg)
{
    char **new_args;
    int i;

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

void free_cmd_set(t_cmd_set *cmd_set)
{
	//TODO free infile, outfile, heredoc_delim if not NULL
    if (!cmd_set)
        return;
    free(cmd_set->name);
    if (cmd_set->args)
    {
        for (int i = 0; cmd_set->args[i]; i++)
            free(cmd_set->args[i]);
        free(cmd_set->args);
    }
    free(cmd_set);
}
