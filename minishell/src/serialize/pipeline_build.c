/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline_build.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: martinmust <martinmust@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/16 20:34:51 by martinmust        #+#    #+#             */
/*   Updated: 2026/03/25 15:27:45 by martinmust       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	handle_redirect_token(t_data *data, t_cmd_set **current_set,
		t_token *token)
{
	if (token->ast_type != LEX_REDIRECT_IN
		&& token->ast_type != LEX_REDIRECT_OUT && token->ast_type != LEX_APPEND)
		return (0);
	if (!token->next)
		return (fprintf(stderr, "Syntax error: missing redirection target\n"),
			1);
	if (!*current_set)
	{
		*current_set = new_cmd_in_pl(data, NULL, NULL);
		if (!*current_set)
			return (1);
	}
	if (token->ast_type == LEX_REDIRECT_IN)
		add_redirect_in_to_cmd_set(data, *current_set, token->next->value);
	else if (token->ast_type == LEX_REDIRECT_OUT)
		add_redirect_out_to_cmd_set(data, *current_set, token->next->value);
	else
		add_append_to_cmd_set(data, *current_set, token->next->value);
	return (0);
}

static int	handle_command_or_arg(t_data *data, t_cmd_set **current_set,
		t_token *token)
{
	if (token->ast_type != LEX_COMMAND && token->ast_type != LEX_ARGS)
		return (0);
	if (!*current_set)
	{
		*current_set = new_cmd_in_pl(data, NULL, token->value);
		return (*current_set == NULL);
	}
	if (!(*current_set)->name)
	{
		(*current_set)->name = ft_strdup(token->value);
		return ((*current_set)->name == NULL);
	}
	if (token->ast_type == LEX_COMMAND)
	{
		fprintf(stderr, "Syntax error: pipe\n");
		return (1);
	}
	return (add_arg_to_cmd_set(*current_set, token->value));
}

static int	handle_heredoc_token(t_data *data, t_cmd_set **current_set,
		t_token *token)
{
	if (token->ast_type != LEX_HEREDOC)
		return (0);
	if (!token->next || token->next->ast_type != LEX_DELIMITER)
	{
		fprintf(stderr, "Syntax error: heredoc\n");
		return (1);
	}
	if (!*current_set)
	{
		*current_set = new_cmd_in_pl(data, NULL, NULL);
		if (!*current_set)
			return (1);
	}
	if ((*current_set)->heredoc_delim)
	{
		fprintf(stderr, "Syntax error: multiple heredoc delimiters\n");
		return (1);
	}
	(*current_set)->heredoc_delim = ft_strdup(token->next->value);
	return ((*current_set)->heredoc_delim == NULL);
}

static int	handle_pipe_token(t_data *data, t_cmd_set **current_set,
		t_token *previous, t_token *token)
{
	if (token->ast_type != LEX_PIPE)
		return (0);
	if (!previous || !token->next || previous->ast_type == LEX_PIPE)
		return (fprintf(stderr, "Syntax error: pipe\n"), 1);
	if (token->next->ast_type != LEX_COMMAND
		&& token->next->ast_type != LEX_REDIRECT_IN
		&& token->next->ast_type != LEX_REDIRECT_OUT
		&& token->next->ast_type != LEX_APPEND
		&& token->next->ast_type != LEX_HEREDOC)
	{
		fprintf(stderr, "Syntax error: pipe\n");
		return (1);
	}
	*current_set = new_cmd_in_pl(data, *current_set, NULL);
	return (*current_set == NULL);
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
		if (handle_pipe_token(data, &current_set, previous, token) != 0
			|| handle_redirect_token(data, &current_set, token) != 0
			|| handle_command_or_arg(data, &current_set, token) != 0
			|| handle_heredoc_token(data, &current_set, token) != 0)
			return (1);
		previous = token;
		token = token->next;
	}
	return (0);
}
