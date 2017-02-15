# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mprevot <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2016/12/01 11:18:53 by mprevot           #+#    #+#              #
#    Updated: 2016/12/02 17:57:54 by mprevot          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC=gcc

CFLAGS=-Wall -Wextra -Werror

RM=rm -f

SRC= ft_arraytolst.c ft_intdup.c ft_intlst_issorted.c \
ft_lstadd_end.c ft_lstcpy.c ft_lstlen.c ft_lstrotate.c \
ft_lstrotate_reverse.c ft_lstsort.c ft_lstsort_rev.c \
ft_printlst.c ft_pushswap_instructs.c ft_pushswap_instructs_p.c \
ft_pushswap_instructs_r.c ft_pushswap_instructs_rr.c \
ft_pushswap_instructs_s.c ft_pushswap_quicksort.c \
ft_pushswap_quicksort_tools0.c ft_pushswap_quicksort_tools1.c \
ft_pushswap_quicksort_tools2.c ft_pushswap_selectsort.c ft_freetvals.c \
ft_pushswap_bublesort.c ft_pushswap_instructs_simplificator.c

OBJS=$(SRC:.c=.o)

%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<

all: push_swap checker

push_swap: $(OBJS) push_swap.o
	make -C libft
	$(CC) $(CFLAGS) $(OBJS) push_swap.o ./libft/libft.a -o push_swap

checker: $(OBJS) checker.o
	make -C libft
	$(CC) $(CFLAGS) $(OBJS) checker.o ./libft/libft.a -o checker

clean:
	$(RM) $(OBJS)
	make -C libft clean

fclean: clean
	$(RM) push_swap checker
	make -C libft fclean

re: fclean all

libft/libft.a:
	make -C libft

.PHONY: clean fclean re all
