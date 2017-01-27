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

intmax_t		ft_printf_getarg_nbr_signed(
	va_list args, t_args a)
{
	intmax_t	nbr;

	nbr = va_arg(args, uintmax_t);
	if (a.lenght == SIZE_HH)
		nbr = (signed char)nbr;
	else if (a.lenght == SIZE_H)
		nbr = (short int)nbr;
	else if (a.lenght == SIZE_L)
		nbr = (long int)nbr;
	else if (a.lenght == SIZE_LL)
		nbr = (long long int)nbr;
	else if (a.lenght == SIZE_J)
		nbr = (intmax_t)nbr;
	else if (a.lenght == SIZE_Z)
		nbr = (ssize_t)nbr;
	else
		nbr = (int)nbr;
	return (nbr);
}

void			ft_printf_nbrlen_signed_len(
	intmax_t nbr, t_args *a, char base)
{
	a->tmp++;
	if (nbr == 0 && a->tmp != 0)
		return ;
	ft_printf_nbrlen_signed_len(nbr / base, a, base);
}

void			ft_printf_putnbr_signed_print(
	intmax_t nbr, t_args *a, char base, int neg)
{
	intmax_t	n;

	a->tmp++;
	if (nbr == 0 && a->tmp != 0)
		return ;
	ft_printf_putnbr_signed_print(nbr / base, a, base, neg);
	n = nbr % base;
	if (neg)
		n = 0 - n;
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

void			ft_printf_putnbr_signed(
	intmax_t nbr, t_args *a, char base, int neg)
{
	int			initial_len;

	ft_printf_nbrlen_signed_len(nbr, a, base);
	initial_len = a->tmp;
	ft_printf_putnbr_signed_printwidth(a, neg);
	ft_printf_putnbr_signed_printargs(a, neg);
	ft_printf_putnbr_signed_printzeros(a, neg);
	if (neg && a->zero == -1)
	{
		ft_putchar('-');
		a->tmp++;
	}
	ft_printf_putnbr_signed_printprecision(a, initial_len);
	initial_len = a->tmp;
	a->tmp = -1;
	if (a->precision != 0 || nbr != 0)
	{
		ft_printf_putnbr_signed_print(nbr, a, base, neg);
		a->tmp = initial_len;
	}
	else
		a->tmp = initial_len - 1;
	ft_printf_putnbr_signed_printafter(a);
}
