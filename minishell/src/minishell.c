/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: martinmust <martinmust@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/08 11:04:06 by smorlier          #+#    #+#             */
/*   Updated: 2026/03/25 01:44:30 by martinmust       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	handle_empty_signal(t_data *data, char *cmd, int status)
{
	if (!status)
		return (0);
	data->exit_code = status;
	if (cmd[0] != '\0')
		return (0);
	free(cmd);
	return (1);
}

static int	prepare_command_input(t_data *data, char *cmd)
{
	int	token_status;

	if (cmd[0] != '\0')
		add_history(cmd);
	if (data->tokens)
		free_tokens(data->tokens);
	data->tokens = NULL;
	if (data->t_pipeline)
		free_pipeline(data);
	token_status = tokenizer(cmd, &data->tokens);
	free(cmd);
	if (token_status != 0)
	{
		free_tokens(data->tokens);
		data->tokens = NULL;
		data->exit_code = 2;
		return (0);
	}
	if (!data->tokens)
	{
		data->exit_code = 0;
		return (0);
	}
	return (1);
}

static void	process_command(t_data *data, char *cmd)
{
	if (!prepare_command_input(data, cmd))
		return ;
	if (lexer(data) != 0)
	{
		free_tokens(data->tokens);
		data->tokens = NULL;
		data->exit_code = 2;
		return ;
	}
	if (expand_token(data))
		exit_minishell(data, "Expand failed", 1);
	if (create_pipeline(data) != 0)
	{
		free_pipeline(data);
		free_tokens(data->tokens);
		data->tokens = NULL;
		data->exit_code = 2;
		return ;
	}
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

	data = init_shell_data(env);
	if (!data)
		return (1);
	setup_signals();
	while (1)
	{
		cmd = readline(PROMPT);
		status = consume_signal_status();
		if (!cmd)
			exit_minishell(data, "EOF", 0);
		if (handle_empty_signal(data, cmd, status))
			continue ;
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
