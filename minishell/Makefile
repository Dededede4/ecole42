# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mprevot <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2016/12/01 11:18:53 by mprevot           #+#    #+#              #
#    Updated: 2017/08/06 12:58:13 by mprevot          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC=gcc

CFLAGS=-Wall -Wextra -Werror

RM=rm -f

SRC= main.c

OBJS=$(SRC:.c=.o)

%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<

all: ft_ls

ft_ls: $(OBJS)
	make -C libft
	$(CC) $(CFLAGS) $(OBJS) ./libft/libft.a -o minishell

clean:
	$(RM) $(OBJS)
	make -C libft clean

fclean: clean
	$(RM) ft_ls
	make -C libft fclean

re: fclean all

libft/libft.a:
	make -C libft

.PHONY: clean fclean re all
