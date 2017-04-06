/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_putnbr_signed_args.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mprevot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/24 16:43:36 by mprevot           #+#    #+#             */
/*   Updated: 2017/01/24 16:45:22 by mprevot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void			ft_printf_putnbr_signed_printwidth(
	t_args *a, int neg)
{
	int			spaces;

	if ((a->zero == -1 || a->precision > 0) && a->width != -1 && a->minus == -1)
	{
		if (a->precision != -1 && a->precision > a->tmp)
			spaces = a->width - a->precision;
		else
			spaces = a->width - a->tmp;
		if ((a->plus != -1 && !neg) || (a->space != -1 && !neg))
			spaces--;
		if (neg && a->zero != -1)
			spaces--;
		if (neg && a->zero == -1)
			spaces--;
		if (a->precision == 0)
			spaces++;
		while (spaces-- > 0)
		{
			ft_putchar(' ');
			a->tmp++;
		}
	}
}

void			ft_printf_putnbr_signed_printargs(
	t_args *a, int neg)
{
	if (a->plus != -1 && !neg)
	{
		ft_putchar('+');
		a->tmp++;
	}
	else if (a->space != -1 && !neg)
	{
		ft_putchar(' ');
		a->tmp++;
	}
	if (neg && a->zero != -1)
	{
		ft_putchar('-');
		a->tmp++;
	}
}

void			ft_printf_putnbr_signed_printzeros(
	t_args *a, int neg)
{
	int			spaces;

	if (a->zero != -1 && a->precision == -1
		&& a->width != -1 && a->minus == -1)
	{
		spaces = a->width - a->tmp;
		if (neg && a->zero == -1)
			spaces--;
		while (spaces-- > 0)
		{
			ft_putchar('0');
			a->tmp++;
		}
	}
}

void			ft_printf_putnbr_signed_printprecision(
	t_args *a, int initial_len)
{
	intmax_t	n;

	if (a->precision != -1)
	{
		n = (a->precision > initial_len) ? a->precision - initial_len : 0;
		while (n--)
		{
			write(1, "0", 1);
			a->tmp++;
		}
	}
}

void			ft_printf_putnbr_signed_printafter(
	t_args *a)
{
	int			spaces;

	if (a->width != -1 && a->minus != -1)
	{
		spaces = a->width - a->tmp;
		while (spaces-- > 0)
		{
			ft_putchar(' ');
			a->tmp++;
		}
	}
}
