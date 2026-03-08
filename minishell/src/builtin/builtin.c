/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: martinmust <martinmust@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/25 14:21:47 by steven            #+#    #+#             */
/*   Updated: 2026/03/02 21:04:32 by martinmust       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int is_builtin(t_cmd_set *cmd_set)
{
    if (!cmd_set || !cmd_set->name)
        return (0);
    if (ft_strncmp(cmd_set->name, "pwd", 3) == 0 && cmd_set->name[3] == '\0')
        return (1);
    else if (ft_strncmp(cmd_set->name, "echo", 4) == 0 && cmd_set->name[4] == '\0')
        return (1);
    else if (ft_strncmp(cmd_set->name, "cd", 2) == 0 && cmd_set->name[2] == '\0')
        return (1);
    else if (ft_strncmp(cmd_set->name, "env", 3) == 0 && cmd_set->name[3] == '\0')
        return (1);
    else if (ft_strncmp(cmd_set->name, "export", 6) == 0 && cmd_set->name[6] == '\0')
        return (1);
    else if (ft_strncmp(cmd_set->name, "unset", 5) == 0 && cmd_set->name[5] == '\0')
        return (1);
    else if (ft_strncmp(cmd_set->name, "exit", 4) == 0 && cmd_set->name[4] == '\0')
        return (1);
    return (0);
}

int execute_builtin(t_data *data, t_cmd_set *cmd_set)
{
    if (!cmd_set || !data || !cmd_set->name)
    {
        printf("[ERROR] Invalid command set or data for executing builtin\n");
        return (1);
    }
    if (ft_strncmp(cmd_set->name, "env", 3) == 0 && cmd_set->name[3] == '\0')
    {
        builtin_env(data, cmd_set);
        return (0);
    }
    if (ft_strncmp(cmd_set->name, "export", 6) == 0 && cmd_set->name[6] == '\0')
    {
        builtin_export(data, cmd_set);
        return (0);
    }
    if (ft_strncmp(cmd_set->name, "echo", 4) == 0 && cmd_set->name[4] == '\0')
    {
        builtin_echo(cmd_set);
        return (0);
    }
    if (ft_strncmp(cmd_set->name, "cd", 2) == 0 && cmd_set->name[2] == '\0')
    {
        builtin_cd(cmd_set);
        return (0);
    }
    if (ft_strncmp(cmd_set->name, "pwd", 3) == 0 && cmd_set->name[3] == '\0')
    {
        builtin_pwd();
        return (0);
    }
    if (ft_strncmp(cmd_set->name, "exit", 4) == 0 && cmd_set->name[4] == '\0')
        exit_minishell(data, NULL, 0);
    return (1);
}
