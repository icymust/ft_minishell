/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_build.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: martinmust <martinmust@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/20 00:00:00 by martinmust        #+#    #+#             */
/*   Updated: 2026/03/20 02:08:13 by martinmust       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	copy_current_char(t_expand_state *st, char *value)
{
	st->newval[st->j++] = value[st->i++];
	return (0);
}

static int	next_build_chunk(t_data *data, char *value, char *code,
		t_expand_state *st)
{
	if (update_quote_state(value[st->i], st->quote))
	{
		st->i++;
		return (0);
	}
	if (st->quote[0] || value[st->i] != '$')
		return (copy_current_char(st, value));
	if (value[st->i + 1] == '?')
	{
		append_exit_code(st->newval, &st->j, code);
		st->i += 2;
		return (0);
	}
	if (!(ft_isalpha(value[st->i + 1]) || value[st->i + 1] == '_'))
		return (copy_current_char(st, value));
	return (append_var_value(data, value, st));
}

char	*build_expanded_value(t_data *data, t_token *tok, char *code)
{
	int				len;
	t_expand_state	st;

	len = expanded_value_len(data, tok, code);
	if (len < 0)
		return (NULL);
	st.newval = malloc(len + 1);
	if (!st.newval)
		return (NULL);
	st.quote[0] = 0;
	st.quote[1] = 0;
	st.i = 0;
	st.j = 0;
	while (tok->value[st.i])
	{
		if (next_build_chunk(data, tok->value, code, &st) < 0)
			return (free(st.newval), NULL);
	}
	st.newval[st.j] = '\0';
	return (st.newval);
}
