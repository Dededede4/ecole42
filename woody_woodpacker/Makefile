# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: heynard <heynard@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/05/15 12:23:24 by heynard           #+#    #+#              #
#    Updated: 2019/06/14 14:46:53 by heynard          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME= woody_woodpacker

INCLU_DIR = includes
BUILD_DIR = objs
LIBFT_DIR = libft

SRCS = main.c packer.c binary_check.c files.c crypt.c injection.c

OBJS := $(addprefix $(BUILD_DIR)/,$(patsubst %.c,%.o,$(SRCS)))

CC = gcc
CFLAGS = -Wall -Wextra -Werror
IFLAGS = -I $(INCLU_DIR) -I $(LIBFT_DIR)/includes
LFLAGS =  -L./libft -lft

all: $(NAME)

$(NAME): $(BUILD_DIR) $(OBJS)
	@make -C libft
	$(CC) $(CFLAGS) $(IFLAGS) -o $@ $(OBJS) $(LFLAGS)

$(BUILD_DIR)/%.o: srcs/%.c
	$(CC) $(CFLAGS) -c $< -o $@ -I $(INCLU_DIR)

$(BUILD_DIR):
	@mkdir -p $@

.PHONY: all clean fclean re

clean:
	@make -C libft clean
	rm -rf $(OBJS) $(BUILD_DIR)

fclean: clean
	@make -C libft fclean
	rm -f $(NAME)

re: fclean all
