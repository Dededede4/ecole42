# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mprevot <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2016/12/01 11:18:53 by mprevot           #+#    #+#              #
#    Updated: 2016/12/14 14:40:38 by mprevot          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME=fillit

CC=gcc

CFLAGS=-Wall -Wextra -Werror

RM=rm -f

LDFLAGS=-L.

LDLIBS=-lft

SRC= srcs/tetriminos.c srcs/resolve.c srcs/reader.c srcs/main.c srcs/mapping.c includes/libft/libft.a

$(NAME): libft
	$(CC) $(CFLAGS) $(SRC) -o $(NAME)

libft:
	make -C includes/libft

all: $(NAME)

clean: fclean

fclean:
	$(RM) $(NAME)
	make -C includes/libft fclean

re: fclean all

.PHONY: clean fclean re all
