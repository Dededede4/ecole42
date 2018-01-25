# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mprevot <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2016/12/01 11:18:53 by mprevot           #+#    #+#              #
#    Updated: 2018/01/18 10:52:45 by mprevot          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC=clang++

CFLAGS=-Wall -Werror -Wextra

RM=rm -f

SRC= whatever.cpp

OBJ= whatever

all: whatever

clean:
	@($(RM) $(OBJ))

fclean: clean

re: fclean all

.PHONY: clean fclean re
