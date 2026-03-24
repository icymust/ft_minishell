/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: martinmust <martinmust@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/25 10:21:23 by steven            #+#    #+#             */
/*   Updated: 2026/03/21 23:17:27 by martinmust       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	lex_operators(t_token *token)
{
	if (token->value == NULL)
		return (fprintf(stderr,
				"Lexer error: operator token with null value\n"), 1);
	if (ft_strncmp(token->value, "||", 2) == 0)
		return (fprintf(stderr, "Lexer error: unsupported operator '||'\n"), 1);
	if (ft_strncmp(token->value, "&&", 2) == 0)
		return (fprintf(stderr, "Lexer error: unsupported operator '&&'\n"), 1);
	if (ft_strncmp(token->value, "|", 2) == 0)
		token->ast_type = LEX_PIPE;
	else if (ft_strncmp(token->value, ">>", 3) == 0)
		token->ast_type = LEX_APPEND;
	else if (ft_strncmp(token->value, ">", 2) == 0)
		token->ast_type = LEX_REDIRECT_OUT;
	else if (ft_strncmp(token->value, "<<", 3) == 0)
		token->ast_type = LEX_HEREDOC;
	else if (ft_strncmp(token->value, "<", 2) == 0)
		token->ast_type = LEX_REDIRECT_IN;
	else if (ft_strncmp(token->value, "&", 2) == 0)
		return (fprintf(stderr, "Lexer error: unsupported operator '&'\n"), 1);
	else
		return (fprintf(stderr, "Lexer error: unknown operator '%s'\n",
				token->value), 1);
	return (0);
}

int	lex_words(t_token *token, t_token *previous_token)
{
	if (!token)
		return (0);
	if (previous_token == NULL)
		token->ast_type = LEX_COMMAND;
	else if (previous_token->ast_type == LEX_PIPE)
		token->ast_type = LEX_COMMAND;
	else if (previous_token->ast_type == LEX_REDIRECT_OUT)
		token->ast_type = LEX_PATH;
	else if (previous_token->ast_type == LEX_REDIRECT_IN)
		token->ast_type = LEX_PATH;
	else if (previous_token->ast_type == LEX_APPEND)
		token->ast_type = LEX_PATH;
	else if (previous_token->ast_type == LEX_HEREDOC)
		token->ast_type = LEX_DELIMITER;
	else if (previous_token->ast_type == LEX_COMMAND)
		token->ast_type = LEX_ARGS;
	else if (previous_token->ast_type == LEX_ARGS)
		token->ast_type = LEX_ARGS;
	else
		return (fprintf(stderr,
				"Syntax error: unexpected token after redirection path\n"), 1);
	return (0);
}

int	lexer(t_data *data)
{
	t_token	*previous_token;
	t_token	*token;

	previous_token = NULL;
	if (!data || !data->tokens)
	{
		fprintf(stderr, "Lexer error: invalid input\n");
		return (1);
	}
	token = data->tokens;
	while (token)
	{
		if (token->ast_type == TOKEN_WORD && lex_words(token, previous_token) != 0)
			return (1);
		if (token->ast_type == TOKEN_OPERATOR && lex_operators(token) != 0)
			return (1);
		previous_token = token;
		token = token->next;
	}
	return (0);
}
