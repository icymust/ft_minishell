/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline_parent_builtin.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: martinmust <martinmust@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/16 21:03:40 by martinmust        #+#    #+#             */
/*   Updated: 2026/03/16 21:06:12 by martinmust       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "minishell.h"

int	is_parent_builtin(t_cmd_set *cmd_set)
{
	if (!cmd_set || !cmd_set->name)
		return (0);
	if (ft_strncmp(cmd_set->name, "cd", 2) == 0 && cmd_set->name[2] == '\0')
		return (1);
	if (ft_strncmp(cmd_set->name, "export", 6) == 0
		&& cmd_set->name[6] == '\0')
		return (1);
	if (ft_strncmp(cmd_set->name, "unset", 5) == 0
		&& cmd_set->name[5] == '\0')
		return (1);
	if (ft_strncmp(cmd_set->name, "exit", 4) == 0
		&& cmd_set->name[4] == '\0')
		return (1);
	return (0);
}

int run_parent_builtin(t_data *data, t_cmd_set *cmd_set){
	int saved_stdin;
	int saved_stdout;
	int fd_in;
	int status;

	if (!data || !cmd_set)
		return (1);
	saved_stdin = dup(STDIN_FILENO);
	saved_stdout = dup(STDOUT_FILENO);
	fd_in = -1;
	status = 0;
	if (saved_stdin < 0 || saved_stdout < 0)
		return (perror("dup"), -1);
	if (cmd_set->fd_in != -1)
	{
		if (dup2(cmd_set->fd_in, STDIN_FILENO) < 0)
		return (perror("dup2"), -1);
		close(cmd_set->fd_in);
		cmd_set->fd_in = -1;
	}
	if (cmd_set->infile)
	{
		fd_in = open(cmd_set->infile, O_RDONLY);
		if (fd_in < 0)
		{
			perror("minishell: infile");
			data->exit_code = 1;
			dup2(saved_stdin, STDIN_FILENO);
			dup2(saved_stdout, STDOUT_FILENO);
			close(saved_stdin);
			close(saved_stdout);
			return (1);
		}
		dup2(fd_in, STDIN_FILENO);
		close(fd_in);
	}
	if (cmd_set->outfile)
	{
		int flags = O_WRONLY | O_CREAT | (cmd_set->out_append ? O_APPEND : O_TRUNC);
		int fd_out = open(cmd_set->outfile, flags, 0644);
		if (fd_out < 0)
		{
			perror("minishell: outfile");
			data->exit_code = 1;
			if (dup2(saved_stdin, STDIN_FILENO) < 0 || dup2(saved_stdout, STDOUT_FILENO) < 0)
				perror("dup");
			close(saved_stdin);
			close(saved_stdout);
			return (1);
		}
		dup2(fd_out, STDOUT_FILENO);
		close(fd_out);
	}
	status = execute_builtin(data, cmd_set);
	data->exit_code = status;
	if (dup2(saved_stdin, STDIN_FILENO) < 0 || dup2(saved_stdout, STDOUT_FILENO) < 0)
		perror("dup");
	close(saved_stdin);
	close(saved_stdout);

	return(status);
}
