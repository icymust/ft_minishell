NAME = test
MINISHELL_DIR = ../minishell

all: ${NAME}

$(NAME):
	make all -C ${MINISHELL_DIR}
	@${MINISHELL_DIR}/minishell

re: fclean all

clean:
	$(MAKE) clean -C ${MINISHELL_DIR}

fclean: clean
	$(MAKE) fclean -C ${MINISHELL_DIR}

.PHONY: all clean fclean re $(NAME)