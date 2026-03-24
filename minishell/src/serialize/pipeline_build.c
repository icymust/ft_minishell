/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline_build.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: martinmust <martinmust@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/16 20:34:51 by martinmust        #+#    #+#             */
/*   Updated: 2026/03/25 00:37:26 by martinmust       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	handle_redirect_token(t_data *data, t_cmd_set *current_set,
		t_token *token)
{
	if (token->ast_type != LEX_REDIRECT_IN
		&& token->ast_type != LEX_REDIRECT_OUT && token->ast_type != LEX_APPEND)
		return (0);
	if (!token->next)
	{
		fprintf(stderr, "Syntax error: missing redirection target\n");
		return (1);
	}
	if (!current_set)
	{
		current_set = new_cmd_in_pl(data, current_set, NULL);
		if (!current_set)
			return (1);
	}
	if (token->ast_type == LEX_REDIRECT_IN)
		add_redirect_in_to_cmd_set(data, current_set, token->next->value);
	else if (token->ast_type == LEX_REDIRECT_OUT)
		add_redirect_out_to_cmd_set(data, current_set, token->next->value);
	else
		add_append_to_cmd_set(data, current_set, token->next->value);
	return (0);
}

static int	handle_command_or_arg(t_data *data, t_cmd_set **current_set,
		t_token *token)
{
	if (token->ast_type == LEX_COMMAND)
	{
		*current_set = new_cmd_in_pl(data, *current_set, token->value);
		if (!*current_set)
			return (1);
	}
	if (token->ast_type == LEX_ARGS)
	{
		if (!*current_set)
		{
			fprintf(stderr, "Syntax error: argument without command\n");
			return (1);
		}
		add_arg_to_cmd_set(*current_set, token->value);
	}
	return (0);
}

static int	handle_heredoc_token(t_cmd_set *current_set, t_token *token)
{
	if (token->ast_type != LEX_HEREDOC)
		return (0);
	if (!current_set || !token->next || token->next->ast_type != LEX_DELIMITER)
	{
		fprintf(stderr, "Syntax error: heredoc\n");
		return (1);
	}
	if (current_set->heredoc_delim)
	{
		fprintf(stderr, "Syntax error: multiple heredoc delimiters\n");
		return (1);
	}
	current_set->heredoc_delim = ft_strdup(token->next->value);
	if (!current_set->heredoc_delim)
		return (1);
	return (0);
}

static int	handle_pipe_token(t_token *previous, t_token *token)
{
	if (token->ast_type != LEX_PIPE)
		return (0);
	if (!previous || !token->next || token->next->ast_type != LEX_COMMAND)
	{
		fprintf(stderr, "Syntax error: pipe\n");
		return (1);
	}
	return (0);
}

int	create_pipeline(t_data *data)
{
	t_token		*token;
	t_token		*previous;
	t_cmd_set	*current_set;

	if (!data || !data->tokens)
		return (1);
	data->t_pipeline = NULL;
	current_set = NULL;
	previous = NULL;
	token = data->tokens;
	while (token)
	{
		if (handle_pipe_token(previous, token) != 0
			|| handle_redirect_token(data, current_set, token) != 0
			|| handle_command_or_arg(data, &current_set, token) != 0
			|| handle_heredoc_token(current_set, token) != 0)
			return (1);
		previous = token;
		token = token->next;
	}
	return (0);
}
