/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug_prints.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: steven <steven@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/27 09:25:14 by steven            #+#    #+#             */
/*   Updated: 2026/02/27 10:11:55 by steven           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"



void print_colored_token(t_token *previous_token, t_token *token)
{
	const char	*color;

	if (!previous_token)
        {
		printf("[DBG] Tokens: ");
        color = "\033[0;34m"; // Blue for first token (command)
        }
	else if (token->ast_type == LEX_COMMAND)
		color = "\033[0;34m";
	else if (token->ast_type == LEX_ARGS)
		color = "\033[0;35m";
	else if (token->ast_type == LEX_PATH)
		color = "\033[0;32m";
	else if (token->ast_type == LEX_DELIMITER)
		color = "\033[0;31m";
	else if (token->ast_type == LEX_PIPE)
		color = "\033[0;35m";
	else if (token->ast_type == LEX_REDIRECT_IN
         || token->ast_type == LEX_REDIRECT_OUT 
         || token->ast_type == LEX_APPEND 
         || token->ast_type == LEX_HEREDOC)
		color = "\033[0;33m";
	else
		color = "\033[0;37m";
	printf("%s %s \033[0m", color, token->value);
}

void debug_print_enum(t_lexin_ast ast)
{
    if (ast == TOKEN_WORD)
        printf("TOKEN_WORD");
    else if (ast == TOKEN_OPERATOR)
        printf("TOKEN_OPERATOR");
    else if (ast == LEX_COMMAND)
        printf("LEX_COMMAND");
    else if (ast == LEX_ARGS)
        printf("LEX_ARGS");
    else if (ast == LEX_PATH)
        printf("LEX_PATH");
    else if (ast == LEX_PIPE)
        printf("LEX_PIPE");
    else if (ast == LEX_REDIRECT_IN)
        printf("LEX_REDIRECT_IN");
    else if (ast == LEX_REDIRECT_OUT)
        printf("LEX_REDIRECT_OUT");
    else if (ast == LEX_APPEND)
        printf("LEX_APPEND");
    else if (ast == LEX_HEREDOC)
        printf("LEX_HEREDOC");
    else if (ast == LEX_DELIMITER)
        printf("LEX_DELIMITER");
    else
        printf("UNKNOWN_AST_TYPE");
    printf("\n");
}

void print_cmd_set(t_cmd_set *cmd_set)
{
    if (!cmd_set)
        return;
    printf("Cmd Set:\n");
    printf("Type: %d\n", cmd_set->type);
    printf("Name: %s\n", cmd_set->name);
    printf("Infile: %s\n", cmd_set->infile);
    printf("Outfile: %s\n", cmd_set->outfile);
    printf("Heredoc Delimiter: %s\n", cmd_set->heredoc_delim);
    printf("Args:\n");
    if (cmd_set->args)
    {
        for (int i = 0; cmd_set->args[i]; i++)
            printf("==> %s\n", cmd_set->args[i]);
    }
    else
        printf("  None\n");
    printf("Out Append: %d\n", cmd_set->out_append);
    printf("FD In: %d\n", cmd_set->fd_in);
    printf("FD Out: %d\n", cmd_set->fd_out);
    printf("PID: %d\n", cmd_set->pid);
}