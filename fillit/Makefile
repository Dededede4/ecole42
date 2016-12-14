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

SRC= srcs/creat_tetriminos.c srcs/resolve.c srcs/ft_strlinelen.c srcs/reader.c srcs/error.c srcs/main.c includes/libft/libft.a srcs/ft_sqrt.c

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
