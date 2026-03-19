/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: martinmust <martinmust@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/08 11:04:06 by smorlier          #+#    #+#             */
/*   Updated: 2026/03/19 16:53:21 by martinmust       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	minishell(char **env)
{
	char	*cmd;
	t_data	*data;
	int 	status;

	print_banner();
	cmd = NULL;
	data = malloc(sizeof(t_data));
	status = 0;
	if (!data)
		return (1);
	if (init_data(data, env))
	{
		free_data(data);
		return (1);
	}
	setup_signals();
	while (1)
	{
		cmd = readline(PROMPT);
		status = consume_signal_status();
		if (status)
			data->exit_code = status;
		if (!cmd)
			exit_minishell(data, "EOF", 0);
		if (cmd[0] != '\0')
			add_history(cmd);
		if (data->tokens)
		{
			free_tokens(data->tokens);
			data->tokens = NULL;
		}
		if (data->t_pipeline)
			free_pipeline(data);
		// save tokens in linked list
		if (tokenizer(cmd, &data->tokens) != 0 || !data->tokens)
		{
			free(cmd);
			exit_minishell(data, "Tokenization failed", 1);
		}
		free(cmd);
		cmd = NULL;
		if (lexer(data) != 0)
			exit_minishell(data, "Lexing failed", 1);
		if (expand_token(data))
			exit_minishell(data, "Expand failed", 1);
		// create pipeline
		if (create_pipeline(data) != 0)
			exit_minishell(data, "Pipeline creation failed", 1);
		// print_cmd_set(data->t_pipeline); //DELETE
		if (execute_pipeline(data) < 0)
			exit_minishell(data, "Pipeline execution failed", 1);
		free_pipeline(data);
		free_tokens(data->tokens);
		data->tokens = NULL;
		// fork
		// execute_command(tokens, data->pipe_count, data->cmd_count);
	}
	free_data(data);
	return (0);
}

int	main(int ac, char **av, char **env)
{
	(void)ac;
	(void)av;
	return (minishell(env));
}
