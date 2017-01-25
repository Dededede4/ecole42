NAME=libftprintf.a

CC=gcc

CFLAGS=-Wall -Wextra -Werror

RM=rm -f

LDFLAGS=-L.

LDLIBS=-lft

SRC= libft/ft_memset.c libft/ft_bzero.c libft/ft_memcpy.c libft/ft_memccpy.c libft/ft_memmove.c \
libft/ft_memchr.c libft/ft_memcmp.c libft/ft_strlen.c libft/ft_strdup.c libft/ft_strcpy.c \
libft/ft_strncpy.c libft/ft_strcat.c libft/ft_strncat.c libft/ft_strlcat.c libft/ft_strchr.c \
libft/ft_strrchr.c libft/ft_strncmp.c libft/ft_strstr.c libft/ft_strcmp.c libft/ft_strnstr.c \
libft/ft_atoi.c libft/ft_tolower.c libft/ft_toupper.c libft/ft_isprint.c libft/ft_isascii.c \
libft/ft_isalpha.c libft/ft_isdigit.c libft/ft_isalnum.c libft/ft_memalloc.c libft/ft_memdel.c \
libft/ft_strnew.c libft/ft_strdel.c libft/ft_strclr.c libft/ft_striter.c libft/ft_striteri.c \
libft/ft_strmap.c libft/ft_strmapi.c libft/ft_strequ.c libft/ft_strnequ.c libft/ft_strsub.c \
libft/ft_strjoin.c libft/ft_strtrim.c libft/ft_strsplit.c libft/ft_itoa.c libft/ft_putchar.c \
libft/ft_putstr.c libft/ft_putendl.c libft/ft_putnbr.c libft/ft_putchar.c libft/ft_putendl.c \
libft/ft_putnbr.c libft/ft_putstr.c libft/ft_lstnew.c libft/ft_lstdelone.c libft/ft_lstdel.c \
libft/ft_lstadd.c libft/ft_lstiter.c libft/ft_lstmap.c libft/ft_putchar_fd.c libft/ft_putstr_fd.c \
libft/ft_putendl_fd.c libft/ft_putnbr_fd.c libft/ft_intlen.c libft/ft_memchrf.c \
ft_printf.c ft_printf_putstr.c ft_printf_readarg.c ft_unicode2utf8.c ft_printf_putnbr_signed.c \
ft_intcpy.c ft_unicodedup.c ft_unicodelen.c ft_printf_execarg0.c ft_printf_putnbr_unsigned.c \
ft_printf_execarg1.c ft_printf_execarg2.c ft_printf_putnbr_signed_args.c ft_printf_putnbr_unsigned_args.c \
ft_printf_putstr_args.c ft_isascii_str.c ft_isunicode.c ft_isunicode_str.c ft_printf_tools.c

OBJ=ft_memset.o ft_bzero.o ft_memcpy.o ft_memccpy.o ft_memmove.o \
ft_memchr.o ft_memcmp.o ft_strlen.o ft_strdup.o ft_strcpy.o \
ft_strncpy.o ft_strcat.o ft_strncat.o ft_strlcat.o ft_strchr.o \
ft_strrchr.o ft_strncmp.o ft_strstr.o ft_strcmp.o ft_strnstr.o \
ft_atoi.o ft_tolower.o ft_toupper.o ft_isprint.o ft_isascii.o \
ft_isalpha.o ft_isdigit.o ft_isalnum.o ft_memalloc.o ft_memdel.o \
ft_strnew.o ft_strdel.o ft_strclr.o ft_striter.o ft_striteri.o \
ft_strmap.o ft_strmapi.o ft_strequ.o ft_strnequ.o ft_strsub.o \
ft_strjoin.o ft_strtrim.o ft_strsplit.o ft_itoa.o ft_putchar.o \
ft_putstr.o ft_putendl.o ft_putnbr.o ft_putchar.o ft_putendl.o \
ft_putnbr.o ft_putstr.o ft_lstnew.o ft_lstdelone.o ft_lstdel.o \
ft_lstadd.o ft_lstiter.o ft_lstmap.o ft_putchar_fd.o ft_putstr_fd.o \
ft_putendl_fd.o ft_putnbr_fd.o ft_intlen.o ft_memchrf.o \
ft_printf.o ft_printf_putstr.o ft_printf_readarg.o ft_unicode2utf8.o \
ft_intcpy.o ft_unicodedup.o ft_unicodelen.o ft_printf_execarg0.o \
ft_printf_execarg1.o ft_printf_execarg2.o ft_printf_putnbr_signed.o \
ft_printf_putnbr_unsigned.o ft_printf_putnbr_signed_args.o ft_printf_putnbr_unsigned_args.o \
ft_printf_putstr_args.o ft_isascii_str.o ft_isunicode.o ft_isunicode_str.o ft_printf_tools.o

$(NAME): ft_printf.h
	$(CC) $(CFLAGS) -c $(SRC)
	ar rc $(NAME) $(OBJ)
	ranlib $(NAME)

all: $(NAME)

clean:
	$(RM) $(OBJ)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: clean fclean re all