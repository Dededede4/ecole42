# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: heynard <heynard@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2016/11/12 15:01:03 by heynard           #+#    #+#              #
#    Updated: 2017/06/22 17:41:04 by heynard          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a

CC = gcc

CFLAGS = -Wall -Wextra -Werror
IFLAGS = -I includes/

PATH_CONV = ./srcs/ft_conv/
PATH_MATHS = ./srcs/ft_maths/
PATH_MEM = ./srcs/ft_mem/
PATH_STR = ./srcs/ft_str/
PATH_IS = ./srcs/ft_is/
PATH_LST = ./srcs/ft_lst/
PATH_PRINT = ./srcs/ft_print/
PATH_GNL = ./srcs/get_next_line/
PATH_PRINTF = ./srcs/ft_printf/
PATH_DPRINTF = ./srcs/ft_printf/

SRC_MEM = ft_memset.c\
			ft_bzero.c\
			ft_memcpy.c\
			ft_memccpy.c\
			ft_memmove.c\
			ft_memchr.c\
			ft_memcmp.c\
			ft_memalloc.c\
			ft_memdel.c

SRC_STR = ft_strlen.c\
			ft_strdup.c\
			ft_strcpy.c\
			ft_strncpy.c\
			ft_strcat.c\
			ft_strncat.c\
			ft_strlcat.c\
			ft_strchr.c\
			ft_strrchr.c\
			ft_strstr.c\
			ft_strnstr.c\
			ft_strcmp.c\
			ft_strncmp.c\
			ft_strtrim.c\
			ft_strjoin.c\
			ft_strsub.c\
			ft_strnew.c\
			ft_strdel.c\
			ft_strequ.c\
			ft_strnequ.c\
			ft_strclr.c\
			ft_striter.c\
			ft_striteri.c\
			ft_strmap.c\
			ft_strmapi.c\
			ft_strsplit.c\
			ft_strtolower.c\
			ft_strtoupper.c\
			ft_count_words.c\
			ft_strlen_spec.c\
			ft_count_words_spec.c\
			ft_strcpy_spec.c\
			ft_strrcpy_spec.c\
			ft_strrlen_spec.c\
			ft_strsplit_spec.c\
			ft_strjoin_spec.c\
			ft_strcpy2_spec.c

SRC_IS = ft_isalpha.c\
			ft_isdigit.c\
			ft_isalnum.c\
			ft_isascii.c\
			ft_isprint.c\
			ft_isspace.c\
			ft_isdigit_nozero.c

SRC_PRINT = ft_putchar.c\
			ft_putstr.c\
			ft_putendl.c\
			ft_putnbr.c\
			ft_putchar_fd.c\
			ft_putstr_fd.c\
			ft_putendl_fd.c\
			ft_putnbr_fd.c\
			ft_putcharn.c\
			ft_putcharn_fd.c

SRC_CONV = ft_atoi.c\
			ft_toupper.c\
			ft_tolower.c\
			ft_itoa.c\
			ft_itoa_base.c\
			ft_rev_nbr.c

SRC_LST	= ft_lstnew.c\
			ft_lstdelone.c\
			ft_lstdel.c\
			ft_lstadd.c\
			ft_lstiter.c\
			ft_lstmap.c\

SRC_GNL	= get_next_line.c

SRC_MATHS = ft_count_digits.c\
			ft_count_digits_ularge.c\
			ft_abs_large.c\
			ft_abs.c\
			ft_power.c\

SRC_PRINTF = ft_printf.c\
			parse_arg.c\
			parse_arg_type.c\
			parse_arg_precision.c\
			parse_arg_modifier.c\
			parse_arg_min.c\
			parse_arg_flags.c\
			print_buffer.c\
			write_arg_in_buffer.c\
			write_sint_in_buffer.c\
			write_uint_in_buffer.c\
			write_hexa_in_buffer.c\
			write_octa_in_buffer.c\
			write_char_in_buffer.c\
			write_str_in_buffer.c\
			write_ptr_in_buffer.c\
			write_wchar_in_buffer.c\
			write_wstr_in_buffer.c\
			write_bin_in_buffer.c\
			ft_count_nb.c

SRC_DPRINTF = ft_dprintf.c\
				print_buffer_d.c

PATH_SRC_MATHS = $(addprefix $(PATH_MATHS), $(SRC_MATHS))
PATH_SRC_IS = $(addprefix $(PATH_IS), $(SRC_IS))
PATH_SRC_CONV = $(addprefix $(PATH_CONV), $(SRC_CONV))
PATH_SRC_PRINT = $(addprefix $(PATH_PRINT), $(SRC_PRINT))
PATH_SRC_MEM = $(addprefix $(PATH_MEM), $(SRC_MEM))
PATH_SRC_STR = $(addprefix $(PATH_STR), $(SRC_STR))
PATH_SRC_LST = $(addprefix $(PATH_LST), $(SRC_LST))
PATH_SRC_GNL = $(addprefix $(PATH_GNL), $(SRC_GNL))
PATH_SRC_PRINTF = $(addprefix $(PATH_PRINTF), $(SRC_PRINTF))
PATH_SRC_DPRINTF = $(addprefix $(PATH_DPRINTF), $(SRC_DPRINTF))

OBJ_MATHS = $(PATH_SRC_MATHS:.c=.o)
OBJ_PRINT = $(PATH_SRC_PRINT:.c=.o)
OBJ_IS = $(PATH_SRC_IS:.c=.o)
OBJ_CONV = $(PATH_SRC_CONV:.c=.o)
OBJ_MEM = $(PATH_SRC_MEM:.c=.o)
OBJ_STR = $(PATH_SRC_STR:.c=.o)
OBJ_LST = $(PATH_SRC_LST:.c=.o)
OBJ_GNL = $(PATH_SRC_GNL:.c=.o)
OBJ_PRINTF = $(PATH_SRC_PRINTF:.c=.o)
OBJ_DPRINTF = $(PATH_SRC_DPRINTF:.c=.o)

#include srcs_list.mk

all: $(NAME)

$(NAME): $(OBJ_MATHS) $(OBJ_IS) $(OBJ_GNL) $(OBJ_PRINTF)\
			$(OBJ_STR) $(OBJ_MEM) $(OBJ_LST) $(OBJ_CONV) $(OBJ_PRINT)\
			$(OBJ_DPRINTF)
	@ar rc $(NAME) $^
	@ranlib $(NAME)
	@echo "\033[1;34mlibft\t\t\033[1;33mBuilding\t\t\033[0;32m[OK]\033[0m"

%.o: %.c
	@$(CC) -o $@ -c $< $(CFLAGS) $(IFLAGS)

.PHONY: all clean fclean re

clean:
	@rm -f $(OBJ_MATHS) $(OBJ_IS) $(OBJ_GNL) $(OBJ_PRINTF)\
			$(OBJ_STR) $(OBJ_MEM) $(OBJ_LST) $(OBJ_CONV) $(OBJ_PRINT) $(OBJ_DPRINTF)
	@echo "\033[1;34mlibft\t\t\033[1;33mCleaning objects\t\033[0;32m[OK]\033[0m"

fclean: clean
	@rm -f $(NAME)
	@echo "\033[1;34mlibft\t\t\033[1;33mCleaning libft.a\t\033[0;32m[OK]\033[0m"

re: fclean all
