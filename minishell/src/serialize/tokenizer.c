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

int	add_token(const char *start, const char *end, t_token **tokens,
		t_lexin_ast ast_type)
{
	t_token	*new_token;
	t_token	*temp;

	if (!tokens || !start || !end || end < start)
		return (0);
	new_token = malloc(sizeof(t_token));
	if (!new_token)
		return (0);
	new_token->value = ft_strndup(start, end - start);
	if (!new_token->value)
	{
		free(new_token);
		return (0);
	}
	new_token->next = NULL;
	new_token->ast_type = ast_type;
	if (!*tokens)
		*tokens = new_token;
	else
	{
		temp = *tokens;
		while (temp->next)
			temp = temp->next;
		temp->next = new_token;
	}
	return (1);
}

void	free_tokens(t_token *tokens)
{
	t_token	*temp;

	while (tokens)
	{
		temp = tokens;
		tokens = tokens->next;
		if (temp->value != NULL)
			free(temp->value);
		free(temp);
	}
	tokens = NULL;
}

int	tokenizer(const char *cmd_line, t_token **tokens)
{
	const char	*start;
	char		quote;

	if (!cmd_line || !tokens)
		return (1);
	while (*cmd_line)
	{
		while (*cmd_line && is_space(*cmd_line))
			cmd_line++;
		if (!*cmd_line)
			break ;
		if (*cmd_line && is_operator_char(*cmd_line))
		{
			start = cmd_line;
			if (cmd_line[1] && cmd_line[1] == *cmd_line)
				cmd_line += 2;
			else
				cmd_line++;
			if (!add_token(start, cmd_line, tokens, TOKEN_OPERATOR))
				return (1);
			continue ;
		}
		start = cmd_line;
		while (*cmd_line && !is_space(*cmd_line)
			&& !is_operator_char(*cmd_line))
		{
			if (*cmd_line == '\'' || *cmd_line == '\"')
			{
				quote = *cmd_line++;
				while (*cmd_line && *cmd_line != quote)
					cmd_line++;
				if (*cmd_line != quote)
					return (0);
				if (!*cmd_line)
					return (1);
				cmd_line++;
			}
			else
				cmd_line++;
		}
		if (!add_token(start, cmd_line, tokens, TOKEN_WORD))
			return (1);
	}
	return (0);
}
