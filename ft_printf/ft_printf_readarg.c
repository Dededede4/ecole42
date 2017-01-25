/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mprevot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/26 07:46:40 by mprevot           #+#    #+#             */
/*   Updated: 2017/01/25 16:13:59 by mprevot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		ft_printf_flags(const char *str, t_args *a)
{
	int		i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '#')
			a->hash = 1;
		else if (str[i] == '0')
			a->zero = 1;
		else if (str[i] == '+')
			a->plus = 1;
		else if (str[i] == '-')
			a->minus = 1;
		else if (str[i] == ' ')
			a->space = 1;
		else
			break ;
		i++;
	}
	return (i);
}

int		ft_printf_width(const char *str, t_args *a)
{
	int		i;

	i = 0;
	while (ft_isdigit(str[i]))
		i++;
	if (i)
		a->width = ft_atoi(str);
	return (i);
}

int		ft_printf_precision(const char *str, t_args *a)
{
	int		i;

	i = 0;
	if (str[i] != '.')
		return (i);
	i++;
	a->precision = ft_atoi(str + i);
	while (ft_isdigit(str[i]))
		i++;
	return (i);
}

int		ft_printf_lenght(const char *str, t_args *a)
{
	if (str[0] == 'h' && str[1] == 'h')
	{
		a->lenght = SIZE_HH;
		return (2);
	}
	else if (str[0] == 'l' && str[1] == 'l')
	{
		a->lenght = SIZE_LL;
		return (2);
	}
	else if (str[0] == 'h')
		a->lenght = SIZE_H;
	else if (str[0] == 'l')
		a->lenght = SIZE_L;
	else if (str[0] == 'j')
		a->lenght = SIZE_J;
	else if (str[0] == 'z')
		a->lenght = SIZE_Z;
	else
		return (0);
	return (1);
}

t_args	ft_printf_readarg(const char *str)
{
	int		i;
	t_args	a;

	i = 1;
	a.hash = -1;
	a.zero = -1;
	a.plus = -1;
	a.minus = -1;
	a.space = -1;
	a.precision = -1;
	a.lenght = -1;
	a.type = -1;
	a.tmp = -1;
	a.width = -1;
	a.err = -1;
	i += ft_printf_flags(str + i, &a);
	i += ft_printf_width(str + i, &a);
	i += ft_printf_precision(str + i, &a);
	i += ft_printf_lenght(str + i, &a);
	a.type = str[i];
	i++;
	a.nbr = i;
	return (a);
}
