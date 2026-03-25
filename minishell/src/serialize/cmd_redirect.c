/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_redirect.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: martinmust <martinmust@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/26 16:37:59 by martinmust        #+#    #+#             */
/*   Updated: 2026/03/21 23:16:48 by martinmust       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_redir	*new_redir(t_lexin_ast type, char *filename)
{
	t_redir	*redir;

	redir = malloc(sizeof(t_redir));
	if (!redir)
		return (NULL);
	redir->file = ft_strdup(filename);
	if (!redir->file)
	{
		free(redir);
		return (NULL);
	}
	redir->type = type;
	redir->next = NULL;
	return (redir);
}

static void	append_redir(t_cmd_set *cmd_set, t_lexin_ast type, char *filename)
{
	t_redir	*redir;
	t_redir	*last;

	redir = new_redir(type, filename);
	if (!redir)
		return ;
	if (!cmd_set->redirs)
	{
		cmd_set->redirs = redir;
		return ;
	}
	last = cmd_set->redirs;
	while (last->next)
		last = last->next;
	last->next = redir;
}

void	add_redirect_in_to_cmd_set(t_data *data, t_cmd_set *cmd_set,
		char *filename)
{
	char	*dup_name;

	(void)data;
	if (!cmd_set || !filename || filename[0] == '\0')
		return ;
	append_redir(cmd_set, LEX_REDIRECT_IN, filename);
	dup_name = ft_strdup(filename);
	if (!dup_name)
		return ;
	if (cmd_set->infile)
		free(cmd_set->infile);
	cmd_set->infile = dup_name;
}

void	add_redirect_out_to_cmd_set(t_data *data, t_cmd_set *cmd_set,
		char *filename)
{
	char	*dup_name;

	(void)data;
	if (!cmd_set || !filename || filename[0] == '\0')
		return ;
	append_redir(cmd_set, LEX_REDIRECT_OUT, filename);
	dup_name = ft_strdup(filename);
	if (!dup_name)
		return ;
	if (cmd_set->outfile)
		free(cmd_set->outfile);
	cmd_set->outfile = dup_name;
	cmd_set->out_append = 0;
}

void	add_append_to_cmd_set(t_data *data, t_cmd_set *cmd_set, char *filename)
{
	char	*dup_name;

	(void)data;
	if (!cmd_set || !filename || filename[0] == '\0')
		return ;
	append_redir(cmd_set, LEX_APPEND, filename);
	dup_name = ft_strdup(filename);
	if (!dup_name)
		return ;
	if (cmd_set->outfile)
		free(cmd_set->outfile);
	cmd_set->outfile = dup_name;
	cmd_set->out_append = 1;
}
