NAME = minishell
CC = cc
CFLAGS = -Wall -Wextra -Werror -lreadline
DEBUG_ON = -DDEBUG_MODE=1 -g -fsanitize=address

SRCS = \
	src/builtin/builtin.c \
	src/builtin/builtin_export.c \
	src/builtin/builtin_export_utils.c \
	src/builtin/builtin_unset.c \
	src/builtin/builtin_env.c \
	src/builtin/builtin_echo.c  \
	src/builtin/builtin_cd.c \
	src/builtin/builtin_pwd.c \
	src/data/data.c \
	src/data/envp.c \
	src/execution/execution.c \
	src/execution/execution_external_utils.c \
	src/execution/exec_utils.c \
	src/execution/pipeline_free.c \
	src/execution/cmd_redirections.c \
	src/serialize/tokenizer.c \
	src/serialize/token_list.c \
	src/serialize/lexer.c \
	src/serialize/cmd_set.c \
	src/serialize/cmd_redirect.c \
	src/utils/utils.c \
	src/utils/exit.c \
	src/minishell.c \
	src/serialize/pipeline_build.c \
	src/execution/pipeline_exec.c \
	src/execution/pipeline_heredoc.c \
	src/execution/pipeline_parent_builtin.c \
	src/execution/pipeline_parent_utils.c \
	src/execution/pipeline_parent_redir.c \
	src/core/signals.c \
	src/expand/expand.c \
	src/expand/expand_len.c \
	src/expand/expand_build.c \
	src/expand/expand_utils.c \
	src/execution/pipeline_child.c \
	src/execution/pipeline_exec_utils.c \
	src/serialize/parse_errors.c 


HEADERS = includes/minishell.h

INCLUDE = -I ./includes -I ./libft/includes

LIBFT = -Llibft -lft

-include Makefile.local # delete later

all: libft $(NAME)

$(NAME): ${SRCS} ${HEADERS}
	@$(CC) $(CFLAGS) $(INCLUDE) $(SRCS) $(LIBFT) -o $(NAME)

debug: ${SRCS}
	@$(CC) $(CFLAGS) $(DEBUG_ON) $(INCLUDE) $(SRCS) $(LIBFT) -o $(NAME)

libft:
	@$(MAKE) -C ./libft

re: fclean all

clean:
	$(MAKE) clean -C ./libft

fclean: clean
	$(MAKE) fclean -C ./libft
	rm -f $(NAME)
	rm -rf $(NAME).dSYM

.PHONY: all libft clean fclean re $(NAME) debug


## Mac users need to install readline with `brew install readline` and add the following lines to their .zshrc or .bashrc:
# Local macOS overrides (do not commit).
# READLINE_PREFIX := $(shell brew --prefix readline 2>/dev/null)

# ifeq ($(READLINE_PREFIX),)
# $(error Homebrew readline not found. Run: brew install readline)
# endif

# INCLUDE += -I$(READLINE_PREFIX)/include
# CFLAGS += -L$(READLINE_PREFIX)/lib
