/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_putnbr_unsigned_args.c                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mprevot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/24 18:21:26 by mprevot           #+#    #+#             */
/*   Updated: 2017/01/24 18:21:31 by mprevot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void			ft_printf_putnbr_unsigned_printwidth(
	t_args *a, uintmax_t nbr, char base)
{
	int			spaces;

	if ((a->zero == -1 || a->precision > 0) && a->width != -1 && a->minus == -1)
	{
		if (a->precision != -1 && a->precision > a->tmp)
			spaces = a->width - a->precision;
		else
			spaces = a->width - a->tmp;
		if (a->hash != -1 && (nbr > 0 || a->type == 'p'))
			spaces--;
		if (a->hash != -1 && ((nbr > 0 && base == 16) || a->type == 'p'))
			spaces--;
		if (a->precision == 0 && nbr == 0)
			spaces++;
		while (spaces-- > 0)
		{
			ft_putchar(' ');
			a->tmp++;
		}
	}
}

void			ft_printf_putnbr_unsigned_printhash(
	t_args *a, uintmax_t nbr, char base)
{
	if (a->hash != -1)
	{
		if ((a->type == 'o' && nbr != 0 && a->precision <= a->tmp)
			|| (a->type != 'o' && (nbr > 0 || a->type == 'p')))
		{
			ft_putchar('0');
			a->tmp++;
		}
		if ((nbr > 0 && base == 16) || a->type == 'p')
		{
			ft_putchar((a->type == 'X' ? 'X' : 'x'));
			a->tmp++;
		}
	}
}

void			ft_printf_putnbr_unsigned_printzero(
	t_args *a)
{
	int			spaces;

	if (a->zero != -1 && a->precision == -1
		&& a->width != -1 && a->minus == -1)
	{
		spaces = a->width - a->tmp;
		while (spaces-- > 0)
		{
			ft_putchar('0');
			a->tmp++;
		}
	}
}

void			ft_printf_putnbr_unsigned_printprecision(
	t_args *a, int save)
{
	uintmax_t	n;

	if (a->precision != -1)
	{
		n = (a->precision > save) ? a->precision - save : 0;
		while (n--)
		{
			write(1, "0", 1);
			a->tmp++;
		}
	}
}

void			ft_printf_putnbr_unsigned_printafter(
	t_args *a)
{
	int spaces;

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
