# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gnebie <marvin@42.fr>                      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/03/06 05:39:15 by gnebie            #+#    #+#              #
#    Updated: 2017/03/24 15:16:51 by mprevot          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

.PHONY : clean, fclean, re, all $(NAME)
.SUFFIXES :

CC = gcc
FLAGS = -g -Wall -Werror -Wextra
SPE_FLAGS =
DEBUG_FLAG = -fsanitize=address

NAME = asm

LIB = $(LIB_DIR)libft.a
LIB_DIR = ./../includes/libft/

SRC = compiler.c compiler_content.c compiler_content_hydrating.c \
compiler_content_parsing.c compiler_content_struct.c compiler_header.c \
../includes/share_c/corewar_op_tab.c compiler_error.c

SRC_DIR = ./

OBJ = $(SRC:.c=.o)
OBJ_DIR = ./

INC = ../includes/

all : $(NAME)

$(NAME) : $(LIB) $(OBJ_DIR) $(addprefix $(OBJ_DIR), $(OBJ)) ../includes/corewar.h
	@(echo "\t\t\t\t\t\t\t\t   ____                   __        __           ";)
	@(echo "\t\t\t\t\t\t\t\t  / ___| ___   _ __  ___  \\ \\      / /__ _  _ __ ";)
	@(echo "\t\t\t\t\t\t\t\t | |    / _ \\ | '__|/ _ \\  \\ \\ /\\ / // _\` || '__|";)
	@(echo "\t\t\t\t\t\t\t\t | |___| (_) || |  |  __/   \\ V  V /| (_| || |   ";)
	@(echo "\t\t\t\t\t\t\t\t  \\____|\\___/ |_|   \\___|    \\_/\\_/  \\__,_||_|   ";)
	@($(CC) $(FLAGS) $(SPE_FLAGS) $(addprefix $(OBJ_DIR), $(OBJ)) $(LIB) -I$(INC) -o $(NAME))
	@(echo "\033[33mASM Pret\033[32;6m\n ---Les Champions peuvent commencer la compilation !---\033[0m")

$(LIB) :
	@(cd $(LIB_DIR) && MAKE)

$(OBJ_DIR) :
	mkdir $(OBJ_DIR)

$(OBJ_DIR)%.o : $(addprefix $(SRC_DIR), %.c)
	@($(CC) $(FLAGS) -I$(INC) -c -o $@ $< $(EXTRA_FLAGS))

clean :
	@(rm -f $(addprefix $(OBJ_DIR), $(OBJ)))
	@(echo "\033[33msupression des points o\033[0m")
	@(cd $(LIB_DIR) && MAKE $@)

fclean : clean
	@(rm -f $(NAME))
	@(echo "\033[33msupression de l'asm\033[0m")
	@(cd $(LIB_DIR) && MAKE $@)

re : fclean all
