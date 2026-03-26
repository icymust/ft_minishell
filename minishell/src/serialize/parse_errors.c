/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_errors.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: martinmust <martinmust@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/27 02:22:54 by martinmust        #+#    #+#             */
/*   Updated: 2026/03/27 02:24:22 by martinmust       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	unclosed_quote_error(void)
{
	fprintf(stderr, "Syntax error: unclosed quote\n");
	return (1);
}
