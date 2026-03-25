/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: martinmust <martinmust@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/19 16:53:02 by martinmust        #+#    #+#             */
/*   Updated: 2026/03/25 15:24:08 by martinmust       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	should_expand_token(t_token *tok)
{
	if (!tok || !tok->value)
		return (0);
	if (tok->ast_type == LEX_COMMAND || tok->ast_type == LEX_ARGS)
		return (1);
	return (tok->ast_type == LEX_PATH);
}

static int	should_drop_token(t_token *tok, char *newval)
{
	if (!newval || newval[0] != '\0')
		return (0);
	if (ft_strchr(tok->value, '\'') || ft_strchr(tok->value, '"'))
		return (0);
	return (1);
}

static void	drop_token(t_data *data, t_token *prev, t_token *tok)
{
	if (!prev)
		data->tokens = tok->next;
	else
		prev->next = tok->next;
	free(tok->value);
	free(tok);
}

static int	expand_current_token(t_data *data, char *code, t_token **prev,
		t_token *tok)
{
	char	*newval;

	newval = build_expanded_value(data, tok, code);
	if (!newval)
		return (1);
	if (should_drop_token(tok, newval))
	{
		free(newval);
		drop_token(data, *prev, tok);
		return (0);
	}
	free(tok->value);
	tok->value = newval;
	*prev = tok;
	return (0);
}

int	expand_token(t_data *data)
{
	t_token	*tok;
	t_token	*prev;
	t_token	*next;
	char	*code;

	prev = NULL;
	tok = data->tokens;
	code = ft_itoa(data->exit_code);
	if (!code)
		return (1);
	while (tok)
	{
		next = tok->next;
		if (should_expand_token(tok) && expand_current_token(data, code, &prev,
				tok))
		{
			free(code);
			return (1);
		}
		if (!should_expand_token(tok))
			prev = tok;
		tok = next;
	}
	free(code);
	return (0);
}
