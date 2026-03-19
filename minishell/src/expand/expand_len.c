/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_len.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: martinmust <martinmust@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/20 00:00:00 by martinmust        #+#    #+#             */
/*   Updated: 2026/03/20 02:19:40 by martinmust       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	next_plain_len(t_expand_state *st)
{
	st->i++;
	return (1);
}

static int	next_len_chunk(t_data *data, char *value, char *code,
		t_expand_state *st)
{
	if (update_quote_state(value[st->i], st->quote))
	{
		st->i++;
		return (0);
	}
	if (st->quote[0] || value[st->i] != '$')
		return (next_plain_len(st));
	if (value[st->i + 1] == '?')
	{
		st->i += 2;
		return (ft_strlen(code));
	}
	if (ft_isalpha(value[st->i + 1]) || value[st->i + 1] == '_')
		return (var_value_len(data, value, &st->i));
	return (next_plain_len(st));
}

int	expanded_value_len(t_data *data, t_token *tok, char *code)
{
	int				chunk;
	int				len;
	t_expand_state	st;

	len = 0;
	st.quote[0] = 0;
	st.quote[1] = 0;
	st.i = 0;
	while (tok->value[st.i])
	{
		chunk = next_len_chunk(data, tok->value, code, &st);
		if (chunk < 0)
			return (-1);
		len += chunk;
	}
	return (len);
}
