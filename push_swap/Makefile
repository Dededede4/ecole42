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
ft_pushswap_selectsort.c ft_freetvals.c ft_pushswap_bublesort.c \
ft_pushswap_instructs_simplificator.c libft/libft.a

OBJ=$(SRC:.c=.o)

all: push_swap checker

push_swap:
	make -C libft
	$(CC) $(CFLAGS) push_swap.c $(SRC) -o push_swap

checker:
	make -C libft
	$(CC) $(CFLAGS) checker.c $(SRC) -o checker

clean:
	make -C libft clean

fclean: clean
	$(RM) push_swap checker
	make -C libft fclean

re: fclean all

.PHONY: clean fclean re all
