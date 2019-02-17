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

NAME=libfts.a

CC=/Users/mprevot/.brew/bin/nasm

CFLAGS=-f macho64

RM=rm -f

SRC= bzero.s \
	ft_cat.s \
	isalnum.s \
	isalpha.s \
	isascii.s \
	isdigit.s \
	isprint.s \
	memcpy.s  \
	memset.s \
	puts.s \
	strcat.s \
	strdup.s \
	strlen.s \
	tolower.s \
	toupper.s

OBJ=$(SRC:.s=.o)

all: $(NAME)

%.o: %.s
	$(CC) $(CFLAGS) -o $@ $<

$(NAME): $(OBJ)
	ar rc $(NAME) $(OBJ)
	ranlib $(NAME)

clean:
	$(RM) *.o

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: clean fclean re