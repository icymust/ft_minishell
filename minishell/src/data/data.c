/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: martinmust <martinmust@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/24 18:38:51 by steven            #+#    #+#             */
/*   Updated: 2026/03/21 23:15:41 by martinmust       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	init_data(t_data *data, char **env)
{
	t_token	*tokens;

	tokens = NULL;
	(void)tokens;
	if (!data)
		return (1);
	data->envp = copy_env(env);
	if (data->envp == NULL)
		return (1);
	data->tokens = NULL;
	data->t_pipeline = NULL;
	data->cmd_count = 0;
	data->pipe_count = 0;
	data->exit_code = 0;
	return (0);
}

void	free_data(t_data *data)
{
	int	i;

	i = 0;
	if (!data)
		return ;
	if (data->envp)
	{
		while (data->envp[i])
		{
			free(data->envp[i]);
			i++;
		}
		free(data->envp);
	}
	free_tokens(data->tokens);
	free_pipeline(data);
	data->pipe_count = 0;
	data->cmd_count = 0;
	free(data);
}
