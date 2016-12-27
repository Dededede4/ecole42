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

int	ft_recursive_printf(const char *str, va_list ap)
{
	int		i;
	char	*tmp;
	t_args	a;

	i = 0;
	tmp = ft_strchr(str, '%');
	if (tmp == NULL)
	{
		ft_putstr(str);
		return (0);
	}
	i = tmp - str;
	write(1, str, i);

	a = ft_printf_readarg(str + i);
	ft_printf_synonyms(&a);
	if (a.type == 's')
	{
		if (a.lenght == SIZE_L)
			ft_printf_wputstr(va_arg(ap, wchar_t *), a);
		else
			ft_printf_putstr(va_arg(ap, char *), a);
	}
	else if (a.type == 'p')
		ft_printf_putnbr_pointer(va_arg(ap, int *), a);
	else if (a.type == 'd' || a.type == 'i')
	 	ft_printf_putnbr_signed(va_arg(ap, int), a);
	else if (a.type == 'o')
	 	ft_printf_putnbr_octal(va_arg(ap, int), a);
	else if (a.type == 'u')
		ft_printf_putnbr_unsigned(va_arg(ap, unsigned int), a);
	else if (a.type == 'x')
		ft_printf_putnbr_hexa_min(va_arg(ap, int), a);
	else if (a.type == 'X')
		ft_printf_putnbr_hexa_maj(va_arg(ap, int), a);
	else if (a.type == 'c')
		ft_printf_putchar(va_arg(ap, int), a);
	else if (a.type == '%')
		ft_putchar('%');
	ft_recursive_printf(str + a.nbr, ap);
	return (0);
}

int	ft_printf(const char *format, ...)
{
	va_list ap;

	va_start(ap, format);
	ft_recursive_printf(format, ap);

	va_end(ap);
	return (0);
}