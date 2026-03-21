/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: martinmust <martinmust@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/24 18:21:00 by steven            #+#    #+#             */
/*   Updated: 2026/03/16 21:12:13 by martinmust       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_pipeline(t_data *data)
{
	t_cmd_set	*temp;
	t_cmd_set	*pipeline;

	if (!data)
		return ;
	pipeline = data->t_pipeline;
	while (pipeline)
	{
		temp = pipeline;
		pipeline = pipeline->next;
		free_cmd_set(temp);
	}
	data->t_pipeline = NULL;
}
