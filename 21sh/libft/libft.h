/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mprevot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/11 12:21:34 by mprevot           #+#    #+#             */
/*   Updated: 2017/08/10 21:44:03 by mprevot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# if __STDC_VERSION__ < 199901L
#  define RESTRICT
# endif

# include <unistd.h>
# include <stdlib.h>
# include <string.h>
# include <fcntl.h>
# include <sys/types.h>
# include <sys/uio.h>
# include <stdarg.h>
# include <inttypes.h>

# define BUFF_SIZE 42

# define SIZE_HH 1
# define SIZE_H 2
# define SIZE_L 3
# define SIZE_LL 4
# define SIZE_J 5
# define SIZE_Z 6

# define PERSIST_RETURN 1

# define TRUE 1
# define FALSE 0

# define DEBUG 0

typedef struct			s_fd
{
	int					fd_n;
	int					lastbuff;
	void				*tampon;
	struct s_fd			*next;
}						t_fd;

typedef struct			s_parts_chars
{
	size_t				i;
	size_t				start;
	size_t				count;
	size_t				is_c;
}						t_parts_chars;

typedef struct			s_list
{
	void				*content;
	size_t				content_size;
	struct s_list		*next;
}						t_list;

typedef int				t_unicode;
typedef unsigned char	t_utf8;
typedef char			t_bool;

typedef struct			s_args
{
	char				hash;
	char				zero;
	char				plus;
	char				minus;
	char				space;
	int					width;
	int					precision;
	char				lenght;
	char				type;
	int					nbr;
	int					tmp;
	int					err;
}						t_args;

typedef struct			s_env
{
	char				*key;
	char				*value;
	struct s_env		*next;
}						t_env;

/*
** (for ft_gnl())
** t_buff store the buffer for a specific fd :
**
** fd is the file descriptor
** *content is the buffer (the pointer can move from \n to \n)
** *content_start save the original buffer pointer (for free())
** ended is equal to 1 if the fd is at the end of the file, otherwise 0.
*/

typedef struct			s_buff
{
	int					fd;
	char				*content;
	char				*content_start;
	int					ended;
	struct s_buff		*next;
}						t_buff;

int						get_next_line(const int fd, char **line);
void					*ft_memset(void *b, int c, size_t len);
void					ft_bzero(void *s, size_t n);
void					*ft_memcpy(void *dest, const void *src, size_t n);
void					*ft_memccpy(
							void *dest, const void *src, int c, size_t n);
void					*ft_memmove(void *s1, const void *s2, size_t n);
void					*ft_memchr(const void *s, int c, size_t n);
int						ft_memcmp(const void *s1, const void *s2, size_t n);
size_t					ft_strlen(const char *s);
char					*ft_strdup(const char *s1);
char					*ft_strcpy(char *dst, const char *src);
char					*ft_strncpy(char *dst, const char *src, size_t len);
char					*ft_strcat(char *restrict s1, const char *restrict s2);
char					*ft_strncat(char *restrict s1,
							const char *restrict s2,
							size_t n);
size_t					ft_strlcat(char *restrict dst,
							const char *restrict src,
							size_t size);
char					*ft_strchr(const char *s, int c);
char					*ft_strrchr(const char *s, int c);
int						ft_strncmp(const char *s1, const char *s2, size_t n);
char					*ft_strstr(const char *big, const char *little);
int						ft_strcmp(char *s1, char *s2);
char					*ft_strnstr(const char *big,
							const char *little,
							size_t len);
int						ft_atoi(const char *str);
int						ft_tolower(int c);
int						ft_toupper(int c);
int						ft_isprint(int c);
int						ft_isascii(int c);
int						ft_isalpha(int c);
int						ft_isdigit(int c);
int						ft_isalnum(int c);
void					*ft_memalloc(size_t size);
void					ft_memdel(void **ap);
char					*ft_memdup(char *mem, size_t len);
char					*ft_strnew(size_t size);
void					ft_strdel(char **as);
void					ft_strclr(char *s);
void					ft_striter(char *s, void (*f)(char *));
void					ft_striteri(char *s, void (*f)(unsigned int, char *));
char					*ft_strmap(
							char const *s, char (*f)(char));
char					*ft_strmapi(
							char const *s, char (*f)(unsigned int, char));
int						ft_strequ(char const *s1, char const *s2);
int						ft_strnequ(char const *s1,
							char const *s2,
							size_t n);
char					*ft_strsub(
							char const *s, unsigned int start, size_t len);
char					*ft_strjoin(char const *s1, char const *s2);
char					*ft_strtrim(char const *s);
char					**ft_strsplit(char const *s, char c);
void					ft_strsplit_del(char ***str);
char					*ft_itoa(int n);
void					ft_putchar(char c);
void					ft_putstr(char const *s);
void					ft_putendl(char const *s);
void					ft_putnbr(int n);
void					ft_putchar_fd(char c, int fd);
void					ft_putendl_fd(char const *s, int fd);
void					ft_putnbr_fd(int n, int fd);
void					ft_putstr_fd(char const *s, int fd);
t_list					*ft_lstnew(void const *content, size_t content_size);
void					ft_lstdelone(
							t_list **link, void (*del)(void *, size_t));
void					ft_lstdel(t_list **alst, void (*del)(void*, size_t));
void					ft_lstadd(t_list **alst, t_list *new);
void					ft_lstiter(t_list *lst, void (*f)(t_list *elem));
t_list					*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem));
void					ft_cat(char *path);
int						*ft_range(int min, int max);
int						ft_factorial(int nb);
void					ft_swap(int *a, int *b);
int						ft_gnl(const int fd, char **line);
int						ft_printf(const char *format, ...);
int						ft_vprintf(const char *restrict format, va_list ap);
void					ft_printf_putnbr_pointer(unsigned long nbr, t_args a);
void					ft_printf_wputstr(
	t_unicode *str, t_args *a, int (*f)(t_unicode *, t_args *a));
void					ft_printf_synonyms(t_args *a);
int						ft_printf_flags(const char *str, t_args *a);
int						ft_printf_width(const char *str, t_args *a);
int						ft_printf_precision(const char *str, t_args *a);
int						ft_printf_lenght(const char *str, t_args *a);
t_args					ft_printf_readarg(const char *str);
void					ft_printf_putchar(char c, t_args a);
intmax_t				ft_printf_getarg_nbr_signed(va_list args, t_args a);
uintmax_t				ft_printf_getarg_nbr_unsigned(va_list args, t_args a);
void					ft_printf_putnbr_unsigned
	(uintmax_t nbr, t_args *a, char base);
void					ft_printf_putnbr_signed(
	intmax_t nbr, t_args *a, char base, int neg);
t_utf8					*ft_unicode2utf8(t_unicode *i_str, size_t *size);
int						ft_putstr_utf8(t_unicode *str, t_args *a);
int						ft_putstr_ascii(t_unicode *str, t_args *a);
int						ft_putstr_raw_utf8(t_unicode *str, t_args *a);
int						ft_putstr_raw_ascii(t_unicode *str, t_args *a);
size_t					ft_strsize(t_unicode *str);
void					*ft_intcpy(void *dest, const void *src, size_t n);
t_unicode				*ft_unicodedup(const t_unicode *s1);
size_t					ft_unicodelen(const t_unicode *s);
t_unicode				*ft_wstrdup(const unsigned char *str, size_t len);
int						ft_printf_execarg(t_args *a, va_list ap);
int						ft_printf_execarg_s(t_args *a, va_list ap);
int						ft_printf_execarg_r(t_args *a, va_list ap);
int						ft_printf_execarg_c(t_args *a, va_list ap);
int						ft_printf_execarg_undefineds(t_args *a);
int						ft_printf_execarg_pbdioux(t_args *a, va_list ap);
int						ft_printf_execarg_percent(t_args *a);
void					ft_printf_putnbr_signed_printargs(t_args *a, int neg);
void					ft_printf_putnbr_signed_printwidth(t_args *a, int neg);
void					ft_printf_putnbr_signed_printzeros(t_args *a, int neg);
void					ft_printf_putnbr_signed_printprecision(
	t_args *a, int initial_len);
void					ft_printf_putnbr_signed_printafter(t_args *a);
void					ft_printf_putnbr_unsigned_printwidth(
	t_args *a, uintmax_t nbr, char base);
void					ft_printf_putnbr_unsigned_printhash(
	t_args *a, uintmax_t nbr, char base);
void					ft_printf_putnbr_unsigned_printzero(t_args *a);
void					ft_printf_putnbr_unsigned_printprecision(
	t_args *a, int initial_len);
void					ft_printf_putnbr_unsigned_printafter(t_args *a);
size_t					ft_printf_putstr_printwidth(t_unicode *str, t_args *a);
t_bool					ft_isunicode(t_unicode c);
t_bool					ft_isunicode_str(t_unicode *str);
t_bool					ft_isascii_str(unsigned char *str);
void					ft_printf_synonyms(t_args *a);
int						ft_printf_return(int new_return);
t_unicode				*ft_wstrdup(const unsigned char *str, size_t len);
int						ft_vprintf_tested(const char *restrict str, va_list ap);
int						*ft_intdup(int nbr);
t_bool					ft_intlst_issorted(t_list *lst);
void					ft_lstadd_end(t_list **lst, t_list *new);
t_list					*ft_lstcpy_max(t_list *src, size_t max);
t_list					*ft_lstcpy(t_list *src);
size_t					ft_lstlen(t_list *lst);
void					ft_lstrotate(t_list **lst);
void					ft_lstrotate_reverse(t_list **lst);
t_list					*ft_lstsort(t_list *lst);
t_list					*ft_lstsort_rev(t_list *lst);
void					ft_lstdel_content(t_list **alst);
void					ft_lstdelone_content(t_list **link);
char					*ft_strjoin_multi(int autofree, ...);
t_bool					ft_isdigit_str(char *str);
t_list					*ft_lstlast(t_list *list);
int						ft_intlen(int n);
t_bool					ft_err(char *str);
void					ft_putstr_left(char const *s, size_t place);
void					ft_putstr_right(char const *s, size_t place);
void					ft_putnbr_right(int nbr, size_t place);
void					ft_putnbr_right(int nbr, size_t place);
void					ft_putstr_error(char *str);
void					ft_displayenv();
char					*ft_getenv(char *name);
void					ft_putenv(char *str);
t_env					**ft_env();
void					ft_loadenv();
void					ft_setenv(char *name, char *value, int overwrite);
void					ft_delenv(char *name);
void					ft_delallenv();
char					*ft_strdup_len(char *str, size_t len);
char					*ft_whereis(char *cmd_name);
void					ft_execwait(char *path, char **av);
int						ft_countenv(void);
char					**ft_getpcur(void);
unsigned int			*ft_uintnew(size_t size);
unsigned int			*ft_uintjoin(
	unsigned int const *s1, unsigned int const *s2);
unsigned int			*ft_uintjoin_multi(int autofree, ...);
unsigned int			*ft_uintdup_len(unsigned int *str, size_t len);
char					*ft_uint_to_char(unsigned int *input);
size_t					ft_uintlen(unsigned int const *s);
void					ft_uintputchar(unsigned int const *str);
void					ft_uintput(unsigned int *str);
unsigned int			*ft_uintdup(unsigned int const *s1);
void					ft_uintdel(unsigned int **as);
unsigned int			*ft_uintsub(
	unsigned int const *s, unsigned int start, size_t len);
unsigned int			*ft_uinttrim_free(unsigned int **str);
int						ft_atoi_uint(const unsigned int *str);
int						ft_uintcmp(unsigned int *s1, unsigned int *s2);
#endif
