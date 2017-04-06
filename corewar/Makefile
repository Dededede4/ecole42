# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gnebie <marvin@42.fr>                      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/03/06 05:33:14 by gnebie            #+#    #+#              #
#    Updated: 2017/03/06 05:33:16 by gnebie           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

.PHONY : clean, fclean, re, all, $(ASM_NAME), $(COREWAR_NAME), fall
.SUFFIXES :

CC = gcc
FLAGS = -Wall -Werror -Wextra
SPE_FLAGS =

AUTOR = auteur

COREWAR_NAME = corewar
ASM_NAME = asm
NAME = $(ASM_NAME) $(COREWAR_NAME)

COREWAR_DIR = ./VM/
ASM_DIR = ./compiler/

LIB = $(LIB_DIR)libft.a
LIB_DIR = ./includes/libft/

SRC =
SRC_DIR = ./srcs/

OBJ = $(SRC:.c=.o)
OBJ_DIR = ./objs/

INC = ./includes/

all : $(AUTOR) $(NAME) $(LIB)
	@(cd $(ASM_DIR) && $(MAKE) $(ASM_NAME))
	@(cp $(ASM_DIR)$(ASM_NAME) ./)
	@(cd $(COREWAR_DIR) && $(MAKE) $(COREWAR_NAME))
	@(cp $(COREWAR_DIR)$(COREWAR_NAME) ./)

$(AUTOR) :
	echo "gnebie\nntoniolo\nmprevot" > auteur;

$(LIB) :
	@(cd $(LIB_DIR) && MAKE)

%.o : %.c

$(COREWAR_NAME) : $(LIB)
	@(cd $(COREWAR_DIR) && $(MAKE) $@)
	@(cp $(COREWAR_DIR)$(COREWAR_NAME) ./)

$(ASM_NAME) : $(LIB)
	@(cd $(ASM_DIR) && $(MAKE) $@)
	@(cp $(ASM_DIR)$(ASM_NAME) ./)

clean :
	@(cd $(LIB_DIR) && $(MAKE) $@)
	@(cd $(ASM_DIR) && $(MAKE) $@)
	@(cd $(COREWAR_DIR) && $(MAKE) $@)

fclean :
	@(rm -f $(NAME))
	@(cd $(LIB_DIR) && $(MAKE) $@)
	@(cd $(ASM_DIR) && $(MAKE) $@)
	@(cd $(COREWAR_DIR) && $(MAKE) $@)

re : fclean all
