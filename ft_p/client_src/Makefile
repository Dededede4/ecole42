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

SRC=	client.c \
		command_get.c \
		command_others.c

OBJS=$(SRC:.c=.o)

%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<

all: client

client: $(OBJS)
	make -C ../libft
	make -C ../share
	$(CC) $(CFLAGS) $(OBJS) ../libft/libft.a ../share/share.a -o ../client

clean:
	$(RM) $(OBJS)
	make -C ../libft clean
	make -C ../share clean

fclean: clean
	$(RM) ../client
	make -C ../libft fclean
	make -C ../share fclean

re: fclean all

.PHONY: clean fclean re all
