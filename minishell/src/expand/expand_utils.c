/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: martinmust <martinmust@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/20 00:00:00 by martinmust        #+#    #+#             */
/*   Updated: 2026/03/20 02:19:35 by martinmust       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	update_quote_state(char c, int *quote)
{
	if (c == '\'' && !quote[1])
	{
		quote[0] = !quote[0];
		return (1);
	}
	if (c == '"' && !quote[0])
	{
		quote[1] = !quote[1];
		return (1);
	}
	return (0);
}

char	*expand_var_name(char *value, int *i)
{
	int	start;
	int	len;

	start = *i + 1;
	*i = start;
	while (value[*i] && (ft_isalnum(value[*i]) || value[*i] == '_'))
		(*i)++;
	len = *i - start;
	return (ft_strndup(value + start, len));
}

int	var_value_len(t_data *data, char *value, int *i)
{
	char	*var_name;
	char	*var_value;
	int		len;

	var_name = expand_var_name(value, i);
	if (!var_name)
		return (-1);
	var_value = envp_value(data, var_name);
	len = 0;
	if (var_value)
		len = ft_strlen(var_value);
	free(var_name);
	return (len);
}

void	append_exit_code(char *newval, int *len, char *code)
{
	int	k;

	k = 0;
	while (code[k])
		newval[(*len)++] = code[k++];
}

int	append_var_value(t_data *data, char *value, t_expand_state *st)
{
	char	*var_name;
	char	*var_value;
	int		k;

	var_name = expand_var_name(value, &st->i);
	if (!var_name)
		return (-1);
	var_value = envp_value(data, var_name);
	free(var_name);
	if (!var_value)
		return (0);
	k = 0;
	while (var_value[k])
		st->newval[st->j++] = var_value[k++];
	return (0);
}
