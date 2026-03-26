/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline_exec_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: martinmust <martinmust@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/27 02:09:05 by martinmust        #+#    #+#             */
/*   Updated: 2026/03/27 02:09:05 by martinmust       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	restore_signals_fail(void)
{
	setup_signals();
	return (-1);
}
