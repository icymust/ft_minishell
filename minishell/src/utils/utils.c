/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: martinmust <martinmust@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/23 19:04:15 by martinmust        #+#    #+#             */
/*   Updated: 2026/03/21 23:30:40 by martinmust       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_space(char c)
{
	return (c == ' ' || (c >= 9 && c <= 13));
}

int	is_operator_char(char c)
{
	return (c == '|' || c == '<' || c == '>' || c == '&');
}

char	*ft_strndup(const char *start, int size)
{
	char	*line;
	int		i;

	i = 0;
	line = malloc(size + 1);
	if (!line)
		return (NULL);
	while (i < size)
	{
		line[i] = start[i];
		i++;
	}
	line[i] = '\0';
	return (line);
}

void	clear_command_state(t_data *data)
{
	if (!data)
		return ;
	if (data->t_pipeline)
		free_pipeline(data);
	if (data->tokens)
		free_tokens(data->tokens);
	data->t_pipeline = NULL;
	data->tokens = NULL;
}

void	free_cmd_allocs(t_cmd_set *cmd_set)
{
	int		i;
	t_redir	*next_redir;

	i = 0;
	while (cmd_set->redirs)
	{
		next_redir = cmd_set->redirs->next;
		free(cmd_set->redirs->file);
		free(cmd_set->redirs);
		cmd_set->redirs = next_redir;
	}
	while (cmd_set->args && cmd_set->args[i])
		free(cmd_set->args[i++]);
	free(cmd_set->args);
}
