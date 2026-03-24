/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: martinmust <martinmust@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/24 22:15:31 by martinmust        #+#    #+#             */
/*   Updated: 2026/03/24 00:51:15 by martinmust       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_quote(char c)
{
	return (c == '\'' || c == '\"');
}

static int	is_n_option(const char *s)
{
	int	i;

	if (!s || s[0] != '-')
		return (0);
	i = 1;
	if (s[i] == '\0')
		return (0);
	while (s[i])
	{
		if (s[i] != 'n')
			return (0);
		i++;
	}
	return (1);
}


static void	print_echo_arg(char *str)
{
	int	len;
	int	start;
	int	end;

	if (!str)
		return ;
	len = (int)ft_strlen(str);
	start = 0;
	end = len;
	if (len >= 2 && is_quote(str[0]) && str[0] == str[len - 1])
	{
		start = 1;
		end = len - 1;
	}
	while (start < end)
		printf("%c", str[start++]);
}

void	builtin_echo(t_cmd_set *cmd_set)
{
	int	newline;
	int	i;

	newline = 1;
	i = 0;
	if (!cmd_set->args || !cmd_set->args || cmd_set->args[0] == NULL)
	{
		printf("\n");
		return ;
	}
	if (is_n_option(cmd_set->args[i]))
	{
		newline = 0;
		i++;
	}
	while (cmd_set->args[i])
	{
		print_echo_arg(cmd_set->args[i++]);
		if (cmd_set->args[i])
			printf(" ");
	}
	if (newline)
		printf("\n");
}
