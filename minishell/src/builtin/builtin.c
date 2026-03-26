/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: martinmust <martinmust@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/25 14:21:47 by steven            #+#    #+#             */
/*   Updated: 2026/03/21 22:07:51 by martinmust       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_numeric_exit_arg(char *arg)
{
	int	i;

	if (!arg || !arg[0])
		return (0);
	i = 0;
	if (arg[i] == '+' || arg[i] == '-')
		i++;
	if (!arg[i])
		return (0);
	while (arg[i])
	{
		if (!ft_isdigit(arg[i]))
			return (0);
		i++;
	}
	return (1);
}

static int	exit_code_from_arg(char *arg)
{
	long long	value;
	int			sign;

	value = 0;
	sign = 1;
	if (*arg == '+' || *arg == '-')
		if (*arg++ == '-')
			sign = -1;
	while (*arg)
	{
		value = (value * 10) + (*arg - '0');
		arg++;
	}
	return ((unsigned char)(value * sign));
}

static int	run_exit_builtin(t_data *data, t_cmd_set *cmd_set)
{
	if (!cmd_set->args || !cmd_set->args[0])
		exit_minishell(data, NULL, data->exit_code);
	if (!is_numeric_exit_arg(cmd_set->args[0]))
	{
		fprintf(stderr, "exit: numeric argument required\n");
		exit_minishell(data, NULL, 255);
	}
	if (cmd_set->args[1])
	{
		fprintf(stderr, "exit: too many arguments\n");
		return (1);
	}
	exit_minishell(data, NULL, exit_code_from_arg(cmd_set->args[0]));
	return (0);
}

int	is_builtin(t_cmd_set *cmd_set)
{
	if (!cmd_set || !cmd_set->name)
		return (0);
	if (ft_strncmp(cmd_set->name, "pwd", 3) == 0 && cmd_set->name[3] == '\0')
		return (1);
	else if (ft_strncmp(cmd_set->name, "echo", 4) == 0
		&& cmd_set->name[4] == '\0')
		return (1);
	else if (ft_strncmp(cmd_set->name, "cd", 2) == 0
		&& cmd_set->name[2] == '\0')
		return (1);
	else if (ft_strncmp(cmd_set->name, "env", 3) == 0
		&& cmd_set->name[3] == '\0')
		return (1);
	else if (ft_strncmp(cmd_set->name, "export", 6) == 0
		&& cmd_set->name[6] == '\0')
		return (1);
	else if (ft_strncmp(cmd_set->name, "unset", 5) == 0
		&& cmd_set->name[5] == '\0')
		return (1);
	else if (ft_strncmp(cmd_set->name, "exit", 4) == 0
		&& cmd_set->name[4] == '\0')
		return (1);
	return (0);
}

int	execute_builtin(t_data *data, t_cmd_set *cmd_set)
{
	if (!cmd_set || !data || !cmd_set->name)
		return (1);
	if (ft_strncmp(cmd_set->name, "env", 3) == 0 && cmd_set->name[3] == '\0')
		return (builtin_env(data, cmd_set));
	if (ft_strncmp(cmd_set->name, "export", 6) == 0 && cmd_set->name[6] == '\0')
		return (builtin_export(data, cmd_set));
	if (ft_strncmp(cmd_set->name, "echo", 4) == 0 && cmd_set->name[4] == '\0')
	{
		builtin_echo(cmd_set);
		return (0);
	}
	if (ft_strncmp(cmd_set->name, "cd", 2) == 0 && cmd_set->name[2] == '\0')
		return (builtin_cd(data, cmd_set));
	if (ft_strncmp(cmd_set->name, "pwd", 3) == 0 && cmd_set->name[3] == '\0')
	{
		builtin_pwd();
		return (0);
	}
	if (ft_strncmp(cmd_set->name, "unset", 5) == 0 && cmd_set->name[5] == '\0')
		return (builtin_unset(data, cmd_set));
	if (ft_strncmp(cmd_set->name, "exit", 4) == 0 && cmd_set->name[4] == '\0')
		return (run_exit_builtin(data, cmd_set));
	return (1);
}
