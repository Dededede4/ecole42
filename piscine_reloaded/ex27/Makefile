# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mprevot <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2016/11/09 15:00:41 by mprevot           #+#    #+#              #
#    Updated: 2016/11/09 17:22:27 by mprevot          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME=ft_display_file

CC=gcc

CFLAGS=-Wall -Wextra -Werror

RM=rm -f

SRC= main.c srcs/*.c

OBJ=*.o

$(NAME):
		$(CC) $(CFLAGS) $(SRC) -o $(NAME)

all: $(NAME)

clean:
		$(RM) $(OBJ)

fclean: clean
		$(RM) $(NAME)

re: fclean all

.PHONY: clean fclean

