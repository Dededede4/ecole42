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
# include "libft/libft.h"

# define SIZE_HH 1
# define SIZE_H 2
# define SIZE_L 3
# define SIZE_LL 4
# define SIZE_J 5
# define SIZE_Z 6


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
	intmax_t 	snbr;
	uintmax_t 	unbr;
	wchar_t 	*str;
	char 		neg;
	
}				t_args;

int     		ft_printf(const char *format, ...);
void			ft_printf_putnbr_pointer(unsigned long nbr, t_args a);
void			ft_printf_wputstr(t_args *a);
void			ft_printf_synonyms(t_args *a);
int				ft_recursive_printf(const char *str, va_list ap);
int	 			ft_printf_flags(const char *str, t_args *a);
int				ft_printf_width(const char *str, t_args *a);
int				ft_printf_precision(const char *str, t_args *a);
int				ft_printf_lenght(const char *str, t_args *a);
t_args			ft_printf_readarg(const char *str);
intmax_t		ft_printf_getarg_nbr_signed(va_list args, t_args a);
uintmax_t		ft_printf_getarg_nbr_unsigned(va_list args, t_args a);
void			ft_printf_putnbr_unsigned(t_args *a);
void			ft_printf_putnbr_signed(t_args *a);
void			ft_printf_putargs(t_args *a, char (*f)(t_args *));
#endif
