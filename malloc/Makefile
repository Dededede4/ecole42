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

CFLAGS=-Wall -Wextra -Werror -Wno-dangling-else

RM=rm -f

SRC=	find_item.c \
		ft_free.c \
		ft_malloc.c \
		ft_memcpy.c \
		ft_memset.c \
		ft_putnbr.c \
		ft_putstr.c \
		ft_realloc.c \
		malloc_direct.c \
		malloc_large_list.c \
		malloc_list.c \
		malloc_nopage_list.c \
		malloc_page_large.c \
		malloc_page_list.c \
		rename_functions.c \
		show_alloc_mem.c

OBJS=$(SRC:.c=.o)

%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<

#ifeq ($(HOSTTYPE),)
#	HOSTTYPE := $(shell uname -m)_$(shell uname -s)
#endif

all: malloc

malloc: $(OBJS)
	$(CC) $(CFLAGS) $(OBJS)  -shared -o libft_malloc_HOSTTYPE.so
	ln -s libft_malloc_HOSTTYPE.so libft_malloc.so

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) libft_malloc.so

re: fclean all

.PHONY: clean fclean re all
