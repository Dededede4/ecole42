# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mprevot <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2016/12/01 11:18:53 by mprevot           #+#    #+#              #
#    Updated: 2018/01/08 16:01:55 by mprevot          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC=clang++

CFLAGS=-Wall -Werror -Wextra

RM=rm -f

SRC= megaphone.cpp

OBJ= megaphone

all: megaphone

clean:
	@($(RM) $(OBJ))

fclean: clean

re: fclean all

.PHONY: clean fclean re
