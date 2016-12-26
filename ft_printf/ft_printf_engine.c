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
	// Synonyme
	if (a.type == 'D')
	{
		a.type = 'd';
		a.lenght = SIZE_L;
	}
	else if (a.type == 'O')
	{
		a.type = 'o';
		a.lenght = SIZE_L;
	}
	else if (a.type == 'U')
	{
		a.type = 'u';
		a.lenght = SIZE_L;
	}
	else if (a.type == 'C')
	{
		a.type = 'c';
		a.lenght = SIZE_L;
	}
	else if (a.type == 'S')
	{
		a.type = 's';
		a.lenght = SIZE_L;
	}

	if (a.type == 's')
	{
		if (a.lenght == SIZE_L)
			ft_printf_wputstr(va_arg(ap, wchar_t *), a);
		else
			ft_printf_putstr(va_arg(ap, char *), a);
	}
	else if (a.type == 'p')
		ft_printf_putnbr_hexa_min(str, a);
	else if (a.type == 'd' || a.type == 'i')
	 	ft_printf_putnbr(str, a);
	else if (a.type == 'o')
	 	ft_printf_putnbr_octal(str, a);
	else if (a.type == 'u')
		ft_printf_putnbr_unsigned(str, a);
	else if (a.type == 'x')
		ft_printf_putnbr_hexa_min(str, a);
	else if (a.type == 'X')
		ft_printf_putnbr_hexa_maj(str, a);
	else if (a.type == 'c')
		ft_printf_putchar(str, a);
	else if (str[i + 1] == '%')
	{
		ft_putchar('%');
		i += 2;
	}
	ft_recursive_printf(str + i, ap);
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