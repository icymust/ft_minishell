# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: smorlier <smorlier@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/07/25 14:05:03 by smorlier          #+#    #+#              #
#    Updated: 2025/08/11 15:59:07 by smorlier         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libftprintf.a

MY_SOURCES = ft_printf.c utils_printf.c 

MY_HEADERS = -I .

MY_OBJECTS = $(MY_SOURCES:.c=.o)

CC = cc
CFLAGS = -Werror -Wall -Wextra

all:  $(NAME)

$(NAME): $(MY_OBJECTS) 
	ar rcs $(NAME) $(MY_OBJECTS)

re: fclean all

clean:
	rm -f $(MY_OBJECTS) $(MY_BONUS_OBJECTS)

fclean: clean 
	rm -f $(NAME)

.PHONY: all clean fclean re

