/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_redirect.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: martinmust <martinmust@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/26 16:37:59 by martinmust        #+#    #+#             */
/*   Updated: 2026/02/26 22:50:40 by martinmust       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void add_redirect_in_to_cmd_set(t_data *data, t_cmd_set *cmd_set, char *filename){
    char *dup_name;

    (void)data;
    if (!cmd_set || !filename || filename[0] == '\0')
        return ;
    dup_name = ft_strdup(filename);
    if (!dup_name)
        return ;
    if (cmd_set->infile)
        free(cmd_set->infile);
    cmd_set->infile = dup_name;
}

void	add_redirect_out_to_cmd_set(t_data *data, t_cmd_set *cmd_set, char *filename)
{
	char	*dup_name;

	(void)data;
	if (!cmd_set || !filename || filename[0] == '\0')
		return ;
	dup_name = ft_strdup(filename);
	if (!dup_name)
		return ;
	if (cmd_set->outfile)
		free(cmd_set->outfile);
	cmd_set->outfile = dup_name;
	cmd_set->out_append = 0;
}


void add_append_to_cmd_set(t_data *data, t_cmd_set *cmd_set, char *filename){
    char *dup_name;

    (void)data;
    if (!cmd_set || !filename || filename[0] == '\0')
        return ;
    dup_name = ft_strdup(filename);
    if (!dup_name)
        return ;
    if (cmd_set->outfile)
        free(cmd_set->outfile);
    cmd_set->outfile = dup_name;
    cmd_set->out_append = 1;
}
