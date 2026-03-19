/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: martinmust <martinmust@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/08 11:04:06 by smorlier          #+#    #+#             */
/*   Updated: 2026/03/19 01:47:15 by martinmust       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static volatile sig_atomic_t	signal_status;

void	handle_sigint(int sig)
{
	(void)sig;
	signal_status = sig;
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

void	setup_wait_signals(void)
{
	struct sigaction	sa;

	sa.sa_handler = SIG_IGN;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = 0;
	sigaction(SIGINT, &sa, NULL);
	sigaction(SIGQUIT, &sa, NULL);
}

int	expand_token(t_data *data)
{
	t_token	*tok;
	char	*newval;
	char	*code;
	char	*var_name;
	char	*var_value;
	int		i;
	int		j;
	int		k;
	int		len;
	int		var_start;
	int		var_len;
	int		in_single;
	int		in_double;

	tok = data->tokens;
	newval = NULL;
	var_name = NULL;
	var_value = NULL;
	code = ft_itoa(data->exit_code);
	if (!code)
		return (1);
	while (tok)
	{
		if ((tok->ast_type == LEX_COMMAND || tok->ast_type == LEX_ARGS
				|| tok->ast_type == LEX_PATH) && tok->value)
		{
			len = 0;
			i = 0;
			in_single = 0;
			in_double = 0;
			while (tok->value[i])
			{
				if (tok->value[i] == '\'' && !in_double)
				{
					in_single = !in_single;
					i++;
				}
				else if (tok->value[i] == '\"' && !in_single)
				{
					in_double = !in_double;
					i++;
				}
				else if (!in_single && tok->value[i] == '$' && tok->value[i
					+ 1] == '?')
				{
					len += ft_strlen(code);
					i += 2;
				}
				else if (!in_single && tok->value[i] == '$'
					&& (ft_isalpha(tok->value[i + 1]) || tok->value[i
						+ 1] == '_'))
				{
					var_start = i + 1;
					i = var_start;
					while (tok->value[i] && (ft_isalnum(tok->value[i])
							|| tok->value[i] == '_'))
						i++;
					var_len = i - var_start;
					var_name = ft_strndup(tok->value + var_start, var_len);
					if (!var_name)
					{
						free(code);
						return (1);
					}
					var_value = envp_value(data, var_name);
					if (var_value)
						len += ft_strlen(var_value);
					free(var_name);
					var_name = NULL;
				}
				else
				{
					len++;
					i++;
				}
			}
			newval = malloc(len + 1);
			if (!newval)
			{
				free(code);
				return (1);
			}
			i = 0;
			j = 0;
			in_single = 0;
			in_double = 0;
			while (tok->value[i])
			{
				if (tok->value[i] == '\'' && !in_double)
				{
					in_single = !in_single;
					i++;
				}
				else if (tok->value[i] == '\"' && !in_single)
				{
					in_double = !in_double;
					i++;
				}
				else if (!in_single && tok->value[i] == '$' && tok->value[i
					+ 1] == '?')
				{
					k = 0;
					while (code[k])
						newval[j++] = code[k++];
					i += 2;
				}
				else if (!in_single && tok->value[i] == '$'
					&& (ft_isalpha(tok->value[i + 1]) || tok->value[i
						+ 1] == '_'))
				{
					var_start = i + 1;
					i = var_start;
					while (tok->value[i] && (ft_isalnum(tok->value[i])
							|| tok->value[i] == '_'))
						i++;
					var_len = i - var_start;
					var_name = ft_strndup(tok->value + var_start, var_len);
					if (!var_name)
					{
						free(newval);
						free(code);
						return (1);
					}
					var_value = envp_value(data, var_name);
					free(var_name);
					var_name = NULL;
					if (var_value)
					{
						k = 0;
						while (var_value[k])
							newval[j++] = var_value[k++];
					}
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
		if (signal_status){
			data->exit_code = 128 + signal_status;
			signal_status = 0;
		}
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
