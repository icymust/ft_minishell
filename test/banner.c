/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   banner.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: steven <steven@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/25 15:23:45 by steven            #+#    #+#             */
/*   Updated: 2026/02/27 18:13:36 by steven           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int print_char(int line_number, int char_number)
{
    const char banner[7][300] = {
    "             ██           ██                                                          ",
    "                                                                                      ",
    "|███     ███ ██ ███    ██ ██ \033[0;34m███████ ██   ██ ███████ ██      ██      \033[0m",
    "|████   ████ ██ ████   ██ ██ \033[0;34m██      ██   ██ ██      ██      ██      \033[0m",
    "|██ |████|██ ██ ██ ██  ██ ██ \033[0;34m███████ ███████ █████   ██      ██      \033[0m",
    "|██  |██ |██ ██ ██  ██ ██ ██ \033[0;34m     ██ ██   ██ ██      ██      ██      \033[0m",
    "|██      |██ ██ ██   ████ ██ \033[0;34m███████ ██   ██ ███████ ███████ ███████ \033[0m"
    };
    if (line_number < 0 || line_number >= 7 || char_number < 0 || char_number >= (int)ft_strlen(banner[line_number]))
        return (0);
    printf("%c", banner[line_number][char_number]);
    return (1);
}
void print_part_banner(int start_char, int end_char)
{
    int line_number;
    int char_number;
    int spacing;
    
    line_number = -1;
    spacing = 0;
    printf("\033[2J\033[H"); // Clear the screen and move cursor to top-left

    while(spacing++ < 5)
        printf(" \n"); 
    while(++line_number < 7)
    {
        char_number = start_char - 1;
        while(++char_number < end_char)
        {
            if(print_char(line_number, char_number) == 0)
                break;
        }
        printf("\n");
        printf("\033[0m");
    }
    printf("\n \033[0m");
    
}
    
void print_banner(void)
{
    int i;
    
    i = 0;
    while(i++ < 200)
    {
        print_part_banner(0, i++);
        usleep(8000); // Sleep for 50 milliseconds
    }
    printf("\033[2J\033[H");
}