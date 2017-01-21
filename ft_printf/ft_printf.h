/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mprevot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/26 08:02:26 by mprevot           #+#    #+#             */
/*   Updated: 2016/12/26 09:26:24 by mprevot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H


# include <stdarg.h>
# include <inttypes.h>
# include "libft/libft.h"

# define SIZE_HH 1
# define SIZE_H 2
# define SIZE_L 3
# define SIZE_LL 4
# define SIZE_J 5
# define SIZE_Z 6

# define PERSIST_RETURN 1


# define TRUE 1
# define FALSE 0


typedef int				t_unicode;
typedef unsigned char	t_utf8;
typedef char 			t_bool;

typedef struct 	s_args
{
	char		hash;
	char		zero;
	char		plus;
	char		minus;
	char		space;
	int			width;
	int			precision;
	char		lenght;
	char		type;
	int			nbr;
	int			tmp;
	int 		err;
	
}				t_args;

int     		ft_printf(const char *format, ...);
int 			ft_vprintf(const char * restrict format, va_list ap);
void			ft_printf_putnbr_pointer(unsigned long nbr, t_args a);
void			ft_printf_wputstr(t_unicode *str, t_args *a, int (*f)(t_unicode *, int precision));
void			ft_printf_synonyms(t_args *a);
int				ft_recursive_printf(const char *str, va_list ap);
int	 			ft_printf_flags(const char *str, t_args *a);
int				ft_printf_width(const char *str, t_args *a);
int				ft_printf_precision(const char *str, t_args *a);
int				ft_printf_lenght(const char *str, t_args *a);
t_args			ft_printf_readarg(const char *str);
void			ft_printf_putchar(char c, t_args a);
intmax_t		ft_printf_getarg_nbr_signed(va_list args, t_args a);
uintmax_t		ft_printf_getarg_nbr_unsigned(va_list args, t_args a);
void			ft_printf_putnbr_unsigned(uintmax_t nbr, t_args *a, char base);
void			ft_printf_putnbr_signed(intmax_t nbr, t_args *a, char base, int neg);
t_utf8			*ft_unicode2utf8(t_unicode *i_str, size_t *size);
int				ft_putstr_utf8(t_unicode *str, int precision);
int				ft_putstr_ascii(t_unicode *str, int precision);
int				ft_putstr_raw_utf8(t_unicode *str, int precision);
int				ft_putstr_raw_ascii(t_unicode *str, int precision);
size_t			ft_strsize(t_unicode *str);
void			*ft_intcpy(void *dest, const void *src, size_t n);
t_unicode		*ft_unicodedup(const t_unicode *s1);
size_t			ft_unicodelen(const t_unicode *s);
#endif
