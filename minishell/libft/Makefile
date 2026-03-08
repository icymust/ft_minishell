# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: smorlier <smorlier@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/07/14 12:57:55 by smorlier          #+#    #+#              #
#    Updated: 2025/12/08 11:17:14 by smorlier         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a

MY_LIBFT = ft_atoi.c ft_memchr.c ft_strlcpy.c \
ft_bzero.c ft_memcmp.c ft_strlen.c \
ft_calloc.c ft_memcpy.c ft_strncmp.c \
ft_isalnum.c ft_memmove.c ft_strnstr.c \
ft_isalpha.c ft_memset.c ft_strrchr.c \
ft_isascii.c ft_strchr.c ft_tolower.c \
ft_isdigit.c ft_strdup.c ft_toupper.c \
ft_isprint.c ft_strlcat.c ft_substr.c \
ft_strjoin.c ft_strtrim.c ft_split.c \
ft_itoa.c ft_strmapi.c ft_striteri.c \
ft_putchar_fd.c ft_putstr_fd.c ft_putendl_fd.c \
ft_putnbr_fd.c ft_lstnew.c ft_lstadd_front.c \
ft_lstsize.c ft_lstlast.c ft_lstadd_back.c \
ft_lstdelone.c ft_lstclear.c ft_lstiter.c ft_lstmap.c

MY_GET_NEXT_LINE = \
	get_next_line.c \
	get_next_line_utils.c
	
MY_LIFT_SRC = $(addprefix src/libft/, $(MY_LIBFT))
MY_PRINTF_SRC = $(addprefix src/ft_printf/, $(MY_PRINTF))
MY_GET_NEXT_LINE_SRC = $(addprefix src/get_next_line/, $(MY_GET_NEXT_LINE))
MY_SOURCES = $(MY_LIFT_SRC) $(MY_PRINTF_SRC) $(MY_GET_NEXT_LINE_SRC)
MY_OBJECTS = $(MY_SOURCES:.c=.o)

MY_HEADERS = -I includes
CC = cc
CFLAGS = -Werror -Wall -Wextra

all: $(NAME)

$(NAME): $(MY_OBJECTS) 
	ar rcs $(NAME) $(MY_OBJECTS)

%.o:%.c
	$(CC) $(CFLAGS) $(MY_HEADERS) -c $< -o $@


re: fclean all

clean:
	rm -f $(MY_OBJECTS)

fclean: clean 
	rm -f $(NAME)

.PHONY: all clean fclean re
