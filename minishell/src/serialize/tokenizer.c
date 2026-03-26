/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: martinmust <martinmust@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/23 19:26:10 by martinmust        #+#    #+#             */
/*   Updated: 2026/03/11 00:14:25 by martinmust       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_token	*new_token_node(const char *start, const char *end,
		t_lexin_ast ast_type)
{
	t_token	*new_token;

	new_token = malloc(sizeof(t_token));
	if (!new_token)
		return (NULL);
	new_token->value = ft_strndup(start, end - start);
	if (!new_token->value)
	{
		free(new_token);
		return (NULL);
	}
	new_token->next = NULL;
	new_token->ast_type = ast_type;
	return (new_token);
}

static int	add_token(const char *start, const char *end, t_token **tokens,
		t_lexin_ast ast_type)
{
	t_token	*new_token;
	t_token	*temp;

	if (!tokens || !start || !end || end < start)
		return (0);
	new_token = new_token_node(start, end, ast_type);
	if (!new_token)
		return (0);
	temp = *tokens;
	if (!temp)
		*tokens = new_token;
	else
	{
		while (temp->next)
			temp = temp->next;
		temp->next = new_token;
	}
	return (1);
}

static int	handle_operator_token(const char **cmd_line, t_token **tokens)
{
	const char	*start;

	start = *cmd_line;
	if ((*cmd_line)[1] && (*cmd_line)[1] == **cmd_line)
		*cmd_line += 2;
	else
		(*cmd_line)++;
	if (!add_token(start, *cmd_line, tokens, TOKEN_OPERATOR))
		return (1);
	return (0);
}

static int	handle_word_token(const char **cmd_line, t_token **tokens)
{
	const char	*start;
	char		quote;

	start = *cmd_line;
	while (**cmd_line && !is_space(**cmd_line) && !is_operator_char(**cmd_line))
	{
		if (**cmd_line == '\'' || **cmd_line == '\"')
		{
			quote = *(*cmd_line)++;
			while (**cmd_line && **cmd_line != quote)
				(*cmd_line)++;
			if (**cmd_line != quote)
				return (unclosed_quote_error());
			if (!**cmd_line)
				return (1);
			(*cmd_line)++;
		}
		else
			(*cmd_line)++;
	}
	if (!add_token(start, *cmd_line, tokens, TOKEN_WORD))
		return (1);
	return (0);
}

int	tokenizer(const char *cmd_line, t_token **tokens)
{
	if (!cmd_line || !tokens)
		return (1);
	while (*cmd_line)
	{
		while (*cmd_line && is_space(*cmd_line))
			cmd_line++;
		if (!*cmd_line)
			break ;
		if (is_operator_char(*cmd_line))
		{
			if (handle_operator_token(&cmd_line, tokens))
				return (1);
		}
		else if (handle_word_token(&cmd_line, tokens))
			return (1);
	}
	return (0);
}
