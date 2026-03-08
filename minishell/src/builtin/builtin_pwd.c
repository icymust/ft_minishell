/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_pwd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: martinmust <martinmust@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/27 22:33:35 by martinmust        #+#    #+#             */
/*   Updated: 2026/02/27 22:38:26 by martinmust       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void builtin_pwd()
{
    char *cwd = getcwd(NULL, 0);
    if (cwd)
    {
        printf("%s\n", cwd);
        free(cwd);
    }
    else
    {
        perror("pwd");
    }
}
