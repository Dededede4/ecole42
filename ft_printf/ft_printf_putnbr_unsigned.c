/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_putnbr.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mprevot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/23 19:10:58 by mprevot           #+#    #+#             */
/*   Updated: 2017/01/23 19:11:00 by mprevot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

uintmax_t		ft_printf_getarg_nbr_unsigned(
	va_list args, t_args a)
{
	uintmax_t	nbr;

	nbr = va_arg(args, uintmax_t);
	if (a.lenght == SIZE_HH)
		nbr = (unsigned char)nbr;
	else if (a.lenght == SIZE_H)
		nbr = (unsigned short int)nbr;
	else if (a.lenght == SIZE_L)
		nbr = (unsigned long int)nbr;
	else if (a.lenght == SIZE_LL)
		nbr = (unsigned long long int)nbr;
	else if (a.lenght == SIZE_J)
		nbr = (uintmax_t)nbr;
	else if (a.lenght == SIZE_Z)
		nbr = (size_t)nbr;
	else if (a.type == 'p')
		nbr = (unsigned long)nbr;
	else
		nbr = (unsigned int)nbr;
	return (nbr);
}

void			ft_printf_nbrlen_unsigned_recursive(
	uintmax_t nbr, t_args *a, char base)
{
	a->tmp++;
	if (nbr == 0 && a->tmp != 0)
		return ;
	ft_printf_nbrlen_unsigned_recursive(nbr / base, a, base);
}

void			ft_printf_putnbr_unsigned_recursive(
	uintmax_t nbr, t_args *a, char base)
{
	uintmax_t	n;

	a->tmp++;
	if (nbr == 0 && a->tmp != 0)
		return ;
	ft_printf_putnbr_unsigned_recursive(nbr / base, a, base);
	n = nbr % base;
	if (n <= 9)
		ft_putchar('0' + n);
	if (n >= 10 && n <= 36)
	{
		if (a->type == 'X')
			ft_putchar('A' + (n - 10));
		else
			ft_putchar('a' + (n - 10));
	}
}

void			ft_printf_putnbr_unsigned(
	uintmax_t nbr, t_args *a, char base)
{
	int			save;

	ft_printf_nbrlen_unsigned_recursive(nbr, a, base);
	save = a->tmp;
	ft_printf_putnbr_unsigned_printwidth(a, nbr, base);
	ft_printf_putnbr_unsigned_printhash(a, nbr, base);
	ft_printf_putnbr_unsigned_printzero(a);
	ft_printf_putnbr_unsigned_printprecision(a, save);
	save = a->tmp;
	a->tmp = -1;
	if ((a->precision != 0 || (a->precision == 0 && nbr != 0))
		|| (a->hash != -1 && a->type == 'o'))
		ft_printf_putnbr_unsigned_recursive(nbr, a, base);
	else
		save--;
	a->tmp = save;
	ft_printf_putnbr_unsigned_printafter(a);
}
