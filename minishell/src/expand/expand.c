/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: martinmust <martinmust@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/19 16:53:02 by martinmust        #+#    #+#             */
/*   Updated: 2026/03/20 02:19:50 by martinmust       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	expand_one_token(t_data *data, t_token *tok, char *code)
{
	char	*newval;

	if ((tok->ast_type != LEX_COMMAND && tok->ast_type != LEX_ARGS
			&& tok->ast_type != LEX_PATH) || !tok->value)
		return (0);
	newval = build_expanded_value(data, tok, code);
	if (!newval)
		return (1);
	free(tok->value);
	tok->value = newval;
	return (0);
}

int	expand_token(t_data *data)
{
	t_token	*tok;
	char	*code;

	tok = data->tokens;
	code = ft_itoa(data->exit_code);
	if (!code)
		return (1);
	while (tok)
	{
		if (expand_one_token(data, tok, code))
		{
			free(code);
			return (1);
		}
		tok = tok->next;
	}
	free(code);
	return (0);
}
