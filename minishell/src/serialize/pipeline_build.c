/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline_build.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: martinmust <martinmust@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/16 20:34:51 by martinmust        #+#    #+#             */
/*   Updated: 2026/03/16 20:36:14 by martinmust       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

int	create_pipeline(t_data *data)
{
	t_token		*token;
	t_cmd_set	*current_set;

	if (!data)
		return (1);
	data->t_pipeline = NULL;
	current_set = NULL;
	if (!data->tokens)
		return (1);
	token = data->tokens;
	while (token)
	{
		if (token->ast_type == LEX_REDIRECT_IN)
		{
			if (!current_set || !token->next)
				return (fprintf(stderr,
						"Syntax error: missing infile after '<'\n"), 1);
			add_redirect_in_to_cmd_set(data, current_set, token->next->value);
		}
		else if (token->ast_type == LEX_REDIRECT_OUT)
		{
			if (!current_set || !token->next)
				return (fprintf(stderr,
						"Syntax error: missing outfile after '>'\n"), 1);
			add_redirect_out_to_cmd_set(data, current_set, token->next->value);
		}
		else if (token->ast_type == LEX_APPEND)
		{
			if (!current_set || !token->next)
				return (fprintf(stderr,
						"Syntax error: missing outfile after '>>'\n"), 1);
			add_append_to_cmd_set(data, current_set, token->next->value);
		}
		if (token->ast_type == LEX_COMMAND)
		{
			current_set = new_cmd_in_pl(data, current_set, token->value);
			if (!current_set)
				return (1);
		}
		if (token->ast_type == LEX_ARGS)
		{
			if (!current_set)
				return (fprintf(stderr,
						"Syntax error: argument without command\n"), 1);
			add_arg_to_cmd_set(current_set, token->value);
		}
		if (token->ast_type == LEX_HEREDOC)
		{
			if (!current_set || !token->next
				|| token->next->ast_type != LEX_DELIMITER)
				return (fprintf(stderr, "Syntax error: heredoc\n"), 1);
			if (current_set->heredoc_delim)
				return (fprintf(stderr,
						"Syntax error: multiple heredoc delimiters for one command\n"),
					1);
			current_set->heredoc_delim = ft_strdup(token->next->value);
		}
		token = token->next;
	}
	return (0);
}
