/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_engine.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mprevot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/26 09:48:59 by mprevot           #+#    #+#             */
/*   Updated: 2016/12/26 09:57:14 by mprevot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_printf_synonyms(t_args *a)
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

wchar_t		*ft_wstrdup(const char *str, size_t len)
{
	wchar_t	*r;

	if (!(r = malloc((len + 1) * sizeof(wchar_t))))
		return (NULL);
	r[len] = '\0';
	while(len--)
		r[len] = str[len];
	return r;
}

int	ft_recursive_printf(const char *str, va_list ap)
{
	int		i;
	char	*tmp;
	intmax_t 	n;
	wchar_t	*s;
	char	c;
	t_args	a;
	int 	printed;

	i = 0;
	tmp = ft_strchr(str, '%');
	if (tmp == NULL)
	{
		ft_putstr(str);
		return (ft_strlen(str));
	}
	i = tmp - str;
	write(1, str, i);

	a = ft_printf_readarg(str + i);
	ft_printf_synonyms(&a);
	if (a.type == 's')
	{
		if (a.lenght == SIZE_L)
		{
			a.str = va_arg(ap, wchar_t *);
			ft_printf_putargs(ft_printf_wputstr, &a);
		}
		else
		{
			tmp = va_arg(ap, char *);
			s = ft_wstrdup(tmp, ft_strlen(tmp));
			if (!s)
				return (0);
			a.str = s;
			ft_printf_putargs(ft_printf_wputstr, &a);
			free(s);
		}
	}
	else if (a.type == 'p')
	{
		a.hash = 1;
		a.base = 16;
		a.unbr = ft_printf_getarg_nbr_unsigned(ap, a);
		ft_printf_putargs(ft_printf_putnbr_unsigned, &a);
	}
	else if (a.type == 'b')
	{
		a.unbr = ft_printf_getarg_nbr_unsigned(ap, a);
		a.base = 2;
		ft_printf_putargs(ft_printf_putnbr_unsigned, &a);
	}
	else if (a.type == 'd' || a.type == 'i')
	{
		a.snbr = ft_printf_getarg_nbr_signed(ap, a);
		a.base = 10;
		a.neg = (a.snbr < 0);
		ft_printf_putargs(ft_printf_putnbr_signed, &a);
	}
	else if (a.type == 'o')
	{
		a.unbr = ft_printf_getarg_nbr_unsigned(ap, a);
		a.base = 8;
		ft_printf_putargs(ft_printf_putnbr_unsigned, &a);
	}
	else if (a.type == 'u')
	{
		a.unbr = ft_printf_getarg_nbr_unsigned(ap, a);
		a.base = 10;
		ft_printf_putargs(ft_printf_putnbr_unsigned, &a);
	}
	else if (a.type == 'x')
	{
		a.unbr = ft_printf_getarg_nbr_unsigned(ap, a);
		a.base = 16;
		ft_printf_putargs(ft_printf_putnbr_unsigned, &a);
	}
	else if (a.type == 'X')
	{
		a.unbr = ft_printf_getarg_nbr_unsigned(ap, a);
		a.base = 16;
		ft_printf_putargs(ft_printf_putnbr_unsigned, &a);
	}
	else if (a.type == 'c')
	{
		c = va_arg(ap, int);
		s = ft_wstrdup(&c, 1);
		if (!s)
			return (0);
		a.str = s;
		ft_printf_putargs(ft_printf_wputstr, &a);
		free(s);
	}
	else if (a.type == '%')
	{
		c = '%';
		s = ft_wstrdup(&c, 1);
		if (!s)
			return (0);
		a.str = s;
		ft_printf_putargs(ft_printf_wputstr, &a);
		free(s);
	}
	printed = i + a.tmp;
	i += a.nbr;
	return ft_recursive_printf(str + i, ap) + printed;
}

int	ft_printf(const char *format, ...)
{
	va_list ap;
	int 	r;

	va_start(ap, format);
	r = ft_recursive_printf(format, ap);

	va_end(ap);
	return (r);
}