/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: martinmust <martinmust@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/08 11:04:06 by smorlier          #+#    #+#             */
/*   Updated: 2026/03/11 03:08:01 by martinmust       ###   ########.fr       */
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

int expand_token(t_data *data)
{
	t_token *tok = data->tokens;
	char *newval = NULL;
	char *code = NULL;
	int i, j, k;

	code = ft_itoa(data->exit_code);
	if (!code)
		return (1);
	while (tok)
	{
		if (tok->ast_type == LEX_ARGS && tok->value)
		{
			int count = 0;
			int len = ft_strlen(tok->value);
			// Считаем количество $?
			for (i = 0; tok->value[i]; ++i)
				if (tok->value[i] == '$' && tok->value[i+1] == '?')
					count++;
			// Выделяем память ровно под результат
			newval = malloc(len - (count * 2) + (count * ft_strlen(code)) + 1);
			if (!newval)
			{
				free(code);
				return (1);
			}
			i = 0;
			j = 0;
			while (tok->value[i])
			{
				if (tok->value[i] == '$' && tok->value[i+1] == '?')
				{
					k = 0;
					while (code[k])
						newval[j++] = code[k++];
					i += 2;
				}
				else
				{
					newval[j++] = tok->value[i++];
				}
			}
			newval[j] = '\0';
			free(tok->value);
			tok->value = newval;
		}
		tok = tok->next;
	}
	free(code);
	return (0);
}

int	minishell(char **env)
{
	char	*cmd;
	t_data	*data;
	
	// print_banner();
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
		if (expand_token(data))
			exit_minishell(data, "Expand failed", 1);
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
