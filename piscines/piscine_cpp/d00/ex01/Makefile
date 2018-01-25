# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mprevot <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2016/12/01 11:18:53 by mprevot           #+#    #+#              #
#    Updated: 2018/01/08 22:44:01 by mprevot          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC=clang++

CFLAGS=-Wall -Wextra -Werror

RM=rm -f

SRC= main.cpp Contact.class.cpp

OBJS=$(SRC:.cpp=.o)

%.o: %.cpp
	$(CC) $(CFLAGS) -c -g -o $@ $<

all: phonebook

phonebook: $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o phonebook

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) phonebook

re: fclean all

.PHONY: clean fclean re all
