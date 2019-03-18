# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mprevot <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2016/12/01 11:18:53 by mprevot           #+#    #+#              #
#    Updated: 2017/02/24 17:54:48 by mprevot          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME=share.a

CC=gcc

CFLAGS=-Wall -Werror -Wextra

RM=rm -f

SRC=	can_read.c \
		can_write.c \
		download_file.c \
		ft_atoi_offt.c \
		ft_itoa_offt_nl.c \
		ft_offtlen.c \
		ft_putofft_fd.c \
		ft_sleep.c \
		is_dir.c \
		send_file.c \
		displayline.c

OBJ=$(SRC:.c=.o)

all: $(NAME)

%.o: %.s
	$(CC) $(CFLAGS) -o $@ $<

$(NAME): $(OBJ)
	ar rc $(NAME) $(OBJ)
	ranlib $(NAME)

clean:
	$(RM) $(OBJ)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: clean fclean re