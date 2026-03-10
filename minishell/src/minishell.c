/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: martinmust <martinmust@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/08 11:04:06 by smorlier          #+#    #+#             */
/*   Updated: 2026/03/10 20:19:33 by martinmust       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int			g_signal = 0;

void	handle_sigint(int sig)
{
	g_signal = sig;
	exit_command(NULL);
}

void	setup_signals(void)
{
	struct sigaction	sa;

	// ctrl c
	sa.sa_handler = handle_sigint;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = SA_RESTART;
	sigaction(SIGINT, &sa, NULL);
	/*ctrl-\*/
	sa.sa_handler = SIG_IGN; // ignore sig
	sigaction(SIGQUIT, &sa, NULL);
}

int	minishell(char **env)
{
	char	*cmd;
	t_data	*data;
	
	print_banner();
	cmd = NULL;
	data = malloc(sizeof(t_data));
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
		//count commands and pipes
		// create pipeline
		if (create_pipeline(data) != 0)
			exit_minishell(data, "Pipeline creation failed", 1);
		if (execute_pipeline(data) < 0)
			exit_minishell(data, "Pipeline execution failed", 1);
		free_pipeline(data);
		free_tokens(data->tokens);
		data->tokens = NULL;
		//fork
		//execute_command(tokens, data->pipe_count, data->cmd_count);
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
