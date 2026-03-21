/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: martinmust <martinmust@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/21 23:28:47 by martinmust        #+#    #+#             */
/*   Updated: 2026/03/21 23:29:24 by martinmust       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/includes/get_next_line.h"
# include "../libft/includes/libft.h"
# include <fcntl.h>
# include <signal.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <unistd.h>
# include <readline/history.h>
# include <readline/readline.h>

# define PROMPT "Minishell>$ "

typedef enum e_lexin_ast
{
	TOKEN_WORD = 0,
	TOKEN_OPERATOR = 1,
	LEX_COMMAND = 11,
	LEX_ARGS = 12,
	LEX_PATH = 13,
	LEX_DELIMITER = 16,
	LEX_PIPE = 02,
	LEX_REDIRECT_IN = 03,
	LEX_REDIRECT_OUT = 04,
	LEX_APPEND = 05,
	LEX_HEREDOC = 06,
}						t_lexin_ast;

typedef struct s_token
{
	char				*value;
	t_lexin_ast			ast_type;
	struct s_token		*next;
}						t_token;

typedef struct s_cmd_set
{
	char				*name;
	char				*infile;
	char				*outfile;
	char				*heredoc_delim;
	char				**args;
	int					out_append;
	int					fd_in;
	int					fd_out;
	pid_t				pid;
	struct s_cmd_set	*next;
}						t_cmd_set;

typedef struct s_data
{
	char				**envp;
	t_token				*tokens;
	int					pipe_count;
	int					cmd_count;
	int					exit_code;
	t_cmd_set			*t_pipeline;
}						t_data;

typedef struct s_expand_state
{
	int					quote[2];
	int					i;
	int					j;
	char				*newval;
}						t_expand_state;

typedef struct s_exec_state
{
	int					fd[2];
	int					prev_fd;
	int					status;
	int					last_status;
	pid_t				pid;
	pid_t				last_pid;
	pid_t				waited_pid;
}						t_exec_state;

int						minishell(char **env);
void					print_banner(void);
int						tokenizer(const char *cmd, t_token **tokens);
void					free_tokens(t_token *tokens);
int						is_space(char c);
int						is_operator_char(char c);
char					*ft_strndup(const char *start, int size);
int						create_pipeline(t_data *data);
int						execute_pipeline(t_data *data);
void					free_pipeline(t_data *data);

int						init_data(t_data *data, char **env);
void					free_data(t_data *data);
char					**copy_env(char **env);

t_cmd_set				*new_cmd_set(char *name);
int						add_arg_to_cmd_set(t_cmd_set *cmd_set, char *arg);
void					free_cmd_set(t_cmd_set *cmd_set);

int						lexer(t_data *data);
int						is_builtin(t_cmd_set *cmd_set);
int						execute_builtin(t_data *data, t_cmd_set *cmd_set);

char					*cmd_found(t_data *data, t_cmd_set *set);
int						prepare_external_exec(t_data *data, t_cmd_set *cmd_set,
							char **cmd_path, char ***argv);
int						builtin_env(t_data *data, t_cmd_set *cmd_set);
int						builtin_export(t_data *data, t_cmd_set *cmd_set);
int						execute_cmd_set(t_cmd_set *cmd_set, t_data *data);

void					builtin_echo(t_cmd_set *cmd_set);
int						builtin_cd(t_data *data, t_cmd_set *cmd_set);
int						builtin_unset(t_data *data, t_cmd_set *cmd_set);
void					builtin_pwd(void);
void					exit_minishell(t_data *data, const char *message,
							int exit_code);
void					exit_command(char *message);

void					add_redirect_in_to_cmd_set(t_data *data,
							t_cmd_set *cmd_set, char *file);
void					add_redirect_out_to_cmd_set(t_data *data,
							t_cmd_set *cmd_set, char *file);
void					add_append_to_cmd_set(t_data *data, t_cmd_set *cmd_set,
							char *file);
int						envp_index(t_data *data, const char *var_name);
void					print_colored_token(t_token *previous_token,
							t_token *token);
void					print_cmd_set(t_cmd_set *cmd_set);
int						create_pipeline(t_data *data);
t_cmd_set				*new_cmd_in_pl(t_data *data, t_cmd_set *current_set,
							char *name);
int						prepare_heredocs(t_cmd_set *pipeline);
int						is_parent_builtin(t_cmd_set *cmd_set);
int						run_parent_builtin(t_data *data, t_cmd_set *cmd_set);
int						save_parent_stdio(int *saved_stdio);
void					restore_parent_stdio(int *saved_stdio);
int						prepare_parent_input(t_data *data, t_cmd_set *cmd_set,
							int *saved_stdio);
int						prepare_parent_output(t_data *data, t_cmd_set *cmd_set,
							int *saved_stdio);
int						is_valid_export_name(char *arg, int name_len);
int						update_or_add_export_entry(t_data *data, char *arg,
							int name_len, int has_equal);
char					*envp_value(t_data *data, const char *var_name);
int						expand_token(t_data *data);
int						update_quote_state(char c, int *quote);
char					*expand_var_name(char *value, int *i);
int						var_value_len(t_data *data, char *value, int *i);
void					append_exit_code(char *newval, int *j, char *code);
int						append_var_value(t_data *data, char *value,
							t_expand_state *st);
int						expanded_value_len(t_data *data, t_token *tok,
							char *code);
char					*build_expanded_value(t_data *data, t_token *tok,
							char *code);
void					setup_signals(void);
void					setup_wait_signals(void);
int						consume_signal_status(void);
void					run_pipeline_child(t_exec_state *state, t_cmd_set *step,
							t_data *data);

#endif
