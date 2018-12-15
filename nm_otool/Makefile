# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mprevot <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/12/15 04:48:08 by mprevot           #+#    #+#              #
#    Updated: 2018/12/15 04:48:10 by mprevot          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC=gcc

CFLAGS=-Wall -Wextra -Werror

RM=rm -f

SRC_NM = nm.c nm_handle.c nm_get_type.c antitroll.c antitroll_get_line.c\
antitroll_handle.c nm_get_line.c nm_tri.c nm_print_line.c nm_segname.c

SRC_OTOOL = otool.c otool_handle.c antitroll.c antitroll_get_line.c\
antitroll_handle.c

OBJS_NM=$(SRC_NM:.c=.o)

OBJS_OTOOL=$(SRC_OTOOL:.c=.o)

%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<

all: ft_nm ft_otool

ft_nm: $(OBJS_NM)
	make -C libft
	$(CC) $(CFLAGS) $(OBJS_NM) ./libft/libft.a -o ft_nm

ft_otool: $(OBJS_OTOOL)
	make -C libft
	$(CC) $(CFLAGS) $(OBJS_OTOOL) ./libft/libft.a -o ft_otool

clean:
	$(RM) $(OBJS_NM) $(OBJS_OTOOL)
	make -C libft clean

fclean: clean
	$(RM) ft_nm ft_otool
	make -C libft fclean

re: fclean all

libft/libft.a:
	make -C libft

.PHONY: clean fclean re all
