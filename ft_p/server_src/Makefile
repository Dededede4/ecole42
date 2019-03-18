# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mprevot <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2016/12/01 11:18:53 by mprevot           #+#    #+#              #
#    Updated: 2017/08/10 21:38:54 by mprevot          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC=gcc

CFLAGS=-Wall -Wextra -Werror

RM=rm -f

SRC= 	command_cd.c \
		command_others.c \
		command_put.c \
		server.c

OBJS=$(SRC:.c=.o)

%.o: %.c
	$(CC) $(CFLAGS) -c -g -o $@ $<

all: server

server: $(OBJS)
	make -C ../libft
	make -C ../share
	$(CC) $(CFLAGS) $(OBJS) ../libft/libft.a ../share/share.a -o ../server

clean:
	$(RM) $(OBJS)
	make -C ../libft clean
	make -C ../share clean

fclean: clean
	$(RM) ../server
	make -C ../libft fclean
	make -C ../share fclean

re: fclean all

.PHONY: clean fclean re all
