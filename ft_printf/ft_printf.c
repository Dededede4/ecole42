/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_engine.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mprevot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/26 09:48:59 by mprevot           #+#    #+#             */
/*   Updated: 2017/01/04 11:37:02 by mprevot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void				ft_printf_synonyms(t_args *a)
{
	if (a->type == 'D')
	{
		a->type = 'd';
		a->lenght = SIZE_L;
	}
	else if (a->type == 'O')
	{
		a->type = 'o';
		a->lenght = SIZE_L;
	}
	else if (a->type == 'U')
	{
		a->type = 'u';
		a->lenght = SIZE_L;
	}
	else if (a->type == 'C')
	{
		a->type = 'c';
		a->lenght = SIZE_L;
	}
	else if (a->type == 'S')
	{
		a->type = 's';
		a->lenght = SIZE_L;
	}
}

t_unicode			*ft_wstrdup(const unsigned char *str, size_t len)
{
	t_unicode		*r;

	if (!(r = malloc((len + 1) * sizeof(t_unicode))))
		return (NULL);
	r[len] = '\0';
	while (len--)
		r[len] = str[len];
	return (r);
}

int					ft_vprintf(const char * restrict str, va_list ap)
{
	int				i;
	char			*tmp;
	intmax_t 		n;
	t_unicode		*s;
	int				c;
	t_args			a;
	int 			printed;
	static int 		old_return = 0;
	int 			new_return;

	i = 0;
	if (str == NULL)
	{
		return (-1);
	}
	tmp = ft_strchr(str, '%');
	if (tmp == NULL)
	{
		ft_putstr(str);
		return (old_return == -1 ? -1 : (int)ft_strlen(str));
	}
	i = tmp - str;
	write(1, str, i);
	a = ft_printf_readarg(str + i);
	ft_printf_synonyms(&a);
	if (a.type == 's')
		ft_printf_execarg_s(&a, ap);
	else if (a.type == 'p')
	{
		a.hash = 1;
		ft_printf_putnbr_unsigned(ft_printf_getarg_nbr_unsigned(ap, a), &a, 16);
	}
	else if (a.type == 'b')
		ft_printf_putnbr_unsigned(ft_printf_getarg_nbr_unsigned(ap, a), &a, 2);
	else if (a.type == 'r')
		ft_printf_execarg_r(&a, ap);
	else if (a.type == 'd' || a.type == 'i')
	{
		n = ft_printf_getarg_nbr_signed(ap, a);
	 	ft_printf_putnbr_signed(n, &a, 10, n < 0);
	}
	else if (a.type == 'o')
	 	ft_printf_putnbr_unsigned(ft_printf_getarg_nbr_unsigned(ap, a), &a, 8);
	else if (a.type == 'u')
		ft_printf_putnbr_unsigned(ft_printf_getarg_nbr_unsigned(ap, a), &a, 10);
	else if (a.type == 'x')
		ft_printf_putnbr_unsigned(ft_printf_getarg_nbr_unsigned(ap, a), &a, 16);
	else if (a.type == 'X')
		ft_printf_putnbr_unsigned(ft_printf_getarg_nbr_unsigned(ap, a), &a, 16);
	else if (a.type == '%')
	{
		c = '%';
		a.width = -1;
		a.precision = -1;
		a.zero = -1;
		s = ft_wstrdup((unsigned char*)(&c), 1);
		if (!s)
			return (-1);
		ft_printf_wputstr(s, &a, ft_putstr_ascii);
		free(s);
	}
	else if (a.type == 'c')
		ft_printf_execarg_c(&a, ap);
	else
	{
		if (a.type != '\0')
		{
			c = a.type;
			if (a.lenght != SIZE_L)
				s = ft_wstrdup((unsigned char*)(&c), 1);
			else
			{
				s = (int *)ft_memalloc(sizeof(int) * 2);
				*s = c;
			}
			if (!s)
				return (-1);
			ft_printf_wputstr(s, &a, ft_putstr_ascii);
			free(s);
		}
		else
			return (0);
	}
	printed = i + a.tmp;
	i += a.nbr;
	if (a.err == 1)
		old_return = -1;
	new_return = ft_vprintf(str + i, ap) + printed;
	if (old_return == -1 && PERSIST_RETURN)
		return -1;
	old_return = new_return;
	return new_return;
}

int				ft_printf(const char *format, ...)
{
	va_list ap;
	int 	r;

	va_start(ap, format);
	r = ft_vprintf(format, ap);

	va_end(ap);
	return (r);
}
