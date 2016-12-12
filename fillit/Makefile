# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mprevot <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2016/12/01 11:18:53 by mprevot           #+#    #+#              #
#    Updated: 2016/12/12 20:45:34 by mprevot          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME=fillit

CC=gcc

CFLAGS=-Wall -Wextra -Werror

RM=rm -f

LDFLAGS=-L.

LDLIBS=-lft

SRC= srcs/creat_tetriminos.c srcs/ft_get_tetriminos_minsize.c srcs/ft_strlinelen.c srcs/reader.c srcs/error.c srcs/main.c includes/libft.a srcs/ft_sqrt.c

$(NAME): fillit
	$(CC) $(CFLAGS) $(SRC) -o $(NAME)

all: $(NAME)

clean: fclean

fclean:
	$(RM) $(NAME)

re: fclean all

.PHONY: clean fclean re all
