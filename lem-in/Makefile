# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mprevot <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2016/12/01 11:18:53 by mprevot           #+#    #+#              #
#    Updated: 2017/02/16 12:17:53 by mprevot          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC=gcc

CFLAGS=-Wall -Wextra -Werror

RM=rm -f

SRC= lemin.c lemin_finder.c lemin_finder_tools.c lemin_moves.c \
lemin_moves_print.c lemin_parser.c lemin_parser_create.c lemin_tools.c 

OBJS=$(SRC:.c=.o)

%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<

all: lem-in
lem_in: lem-in
lemin: lem-in

lem-in: $(OBJS)
	make -C libft
	$(CC) $(CFLAGS) $(OBJS) ./libft/libft.a -o lem-in

clean:
	$(RM) $(OBJS)
	make -C libft clean

fclean: clean
	$(RM) lem-in
	make -C libft fclean

re: fclean all

libft/libft.a:
	make -C libft

.PHONY: clean fclean re all
