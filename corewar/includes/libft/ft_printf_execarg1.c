/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_execarg1.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mprevot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/23 18:25:46 by mprevot           #+#    #+#             */
/*   Updated: 2017/01/23 18:25:52 by mprevot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int					ft_printf_execarg_s(t_args *a, va_list ap)
{
	t_unicode		*s;
	unsigned char	*u;

	if (a->lenght == SIZE_L)
	{
		if (!(s = va_arg(ap, t_unicode *)))
			s = L"(null)";
		ft_printf_wputstr(s, a, ft_putstr_utf8);
	}
	else
	{
		if (!(u = va_arg(ap, unsigned char *)))
			u = (unsigned char*)"(null)";
		s = ft_wstrdup(u, ft_strlen((char *)u));
		if (!s)
			return (-1);
		ft_printf_wputstr(s, a, ft_putstr_ascii);
		free(s);
	}
	return (1);
}

int					ft_printf_execarg_r(t_args *a, va_list ap)
{
	t_unicode		*s;
	unsigned char	*u;

	if (a->lenght == SIZE_L)
	{
		ft_printf_wputstr(va_arg(ap, t_unicode *), a, ft_putstr_raw_utf8);
	}
	else
	{
		u = va_arg(ap, unsigned char *);
		s = ft_wstrdup(u, ft_strlen((char *)u));
		if (!s)
			return (-1);
		ft_printf_wputstr(s, a, ft_putstr_raw_ascii);
		free(s);
	}
	return (1);
}

int					ft_printf_execarg_c(t_args *a, va_list ap)
{
	t_unicode		c;
	t_unicode		*s;

	c = va_arg(ap, int);
	if (a->lenght != SIZE_L)
	{
		s = ft_wstrdup((unsigned char*)(&c), 1);
		if (!s)
			return (-1);
		ft_printf_wputstr(s, a, ft_putstr_ascii);
	}
	else
	{
		s = (t_unicode *)ft_memalloc(sizeof(t_unicode) * 2);
		if (!s)
			return (-1);
		*s = c;
		ft_printf_wputstr(s, a, ft_putstr_utf8);
	}
	free(s);
	return (1);
}

int					ft_printf_execarg_undefineds(t_args *a)
{
	t_unicode		c;
	t_unicode		*s;

	if (a->type != '\0')
	{
		c = a->type;
		a->type = 'u';
		if (a->lenght != SIZE_L)
			s = ft_wstrdup((unsigned char*)(&c), 1);
		else
		{
			s = (int *)ft_memalloc(sizeof(int) * 2);
			*s = c;
		}
		if (!s)
			return (-1);
		ft_printf_wputstr(s, a, ft_putstr_ascii);
		free(s);
		return (1);
	}
	return (0);
}

int					ft_printf_execarg_pbdioux(t_args *a, va_list ap)
{
	intmax_t		n;

	if (a->type == 'b')
		ft_printf_putnbr_unsigned(ft_printf_getarg_nbr_unsigned(ap, *a), a, 2);
	else if (a->type == 'o')
		ft_printf_putnbr_unsigned(ft_printf_getarg_nbr_unsigned(ap, *a), a, 8);
	else if (a->type == 'u')
		ft_printf_putnbr_unsigned(ft_printf_getarg_nbr_unsigned(ap, *a), a, 10);
	else if (a->type == 'x' || a->type == 'X')
		ft_printf_putnbr_unsigned(ft_printf_getarg_nbr_unsigned(ap, *a), a, 16);
	else if (a->type == 'p')
	{
		a->hash = 1;
		ft_printf_putnbr_unsigned(ft_printf_getarg_nbr_unsigned(ap, *a), a, 16);
	}
	else if (a->type == 'd' || a->type == 'i')
	{
		n = ft_printf_getarg_nbr_signed(ap, *a);
		ft_printf_putnbr_signed(n, a, 10, n < 0);
	}
	return (1);
}
