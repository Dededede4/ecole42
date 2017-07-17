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

SRC= algos_sort.c display.c display1.c display2.c extractparams.c\
find_files.c find_files1.c get_date.c lst_file.c lst_sort.c lst_to_tab.c\
main.c recurvise_long_display.c sort_revert.c tab_to_lst.c\
tri_tfile.c tri_tpath.c

OBJS=$(SRC:.c=.o)

%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<

all: ft_ls

ft_ls: $(OBJS)
	make -C libft
	$(CC) $(CFLAGS) -lmlx -framework OpenGL -framework AppKit $(OBJS) ./libft/libft.a -o ft_ls

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
