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

SRC= get_wall_distance.c memset.c mlx.c mlx_okp_0.c \
mlx_okp_1.c parser.c wall.c wolf3d.c

OBJS=$(SRC:.c=.o)

%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<

all: wolf3d

wolf3d: $(OBJS)
	make -C libft
	$(CC) $(CFLAGS) -lmlx -framework OpenGL -framework AppKit $(OBJS) ./libft/libft.a -o wolf3d

clean:
	$(RM) $(OBJS)
	make -C libft clean

fclean: clean
	$(RM) wolf3d
	make -C libft fclean

re: fclean all

libft/libft.a:
	make -C libft

.PHONY: clean fclean re all
