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

static t_data	*init_shell_data(char **env)
{
	t_data	*data;

	data = malloc(sizeof(t_data));
	if (!data)
		return (NULL);
	if (init_data(data, env))
	{
		free_data(data);
		return (NULL);
	}
	return (data);
}

static void	reset_shell_state(t_data *data)
{
	if (data->tokens)
	{
		free_tokens(data->tokens);
		data->tokens = NULL;
	}
	if (data->t_pipeline)
		free_pipeline(data);
}

static void	process_command(t_data *data, char *cmd)
{
	if (cmd[0] != '\0')
		add_history(cmd);
	reset_shell_state(data);
	if (tokenizer(cmd, &data->tokens) != 0 || !data->tokens)
	{
		free(cmd);
		exit_minishell(data, "Tokenization failed", 1);
	}
	free(cmd);
	if (lexer(data) != 0)
		exit_minishell(data, "Lexing failed", 1);
	if (expand_token(data))
		exit_minishell(data, "Expand failed", 1);
	if (create_pipeline(data) != 0)
		exit_minishell(data, "Pipeline creation failed", 1);
	if (execute_pipeline(data) < 0)
		exit_minishell(data, "Pipeline execution failed", 1);
	free_pipeline(data);
	free_tokens(data->tokens);
	data->tokens = NULL;
}

int	minishell(char **env)
{
	char	*cmd;
	t_data	*data;
	int		status;

	print_banner();
	data = init_shell_data(env);
	if (!data)
		return (1);
	setup_signals();
	while (1)
	{
		cmd = readline(PROMPT);
		status = consume_signal_status();
		if (status)
			data->exit_code = status;
		if (!cmd)
			exit_minishell(data, "EOF", 0);
		process_command(data, cmd);
	}
	return (0);
}

int	main(int ac, char **av, char **env)
{
	(void)ac;
	(void)av;
	return (minishell(env));
}
