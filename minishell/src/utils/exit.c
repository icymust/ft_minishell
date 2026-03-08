/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: martinmust <martinmust@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/26 11:25:53 by steven            #+#    #+#             */
/*   Updated: 2026/02/26 16:20:57 by martinmust       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "minishell.h"

void exit_minishell(t_data *data, const char *message, int exit_code)
{
    if (exit_code != 0 && ft_strncmp(message, "EOF", 3) != 0)
        perror("Error");
    if (message && ft_strncmp(message, "EOF", 3) != 0)
        fprintf(stderr, "%s\n", message);
    free_data(data);
    rl_clear_history();
    //TODO kill all child processes if any
    exit(exit_code);
}

void exit_command(char *message)
{
    if (message)
        fprintf(stderr, "%s\n", message);
    //TODO kill all child processes if any
	write(1, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}