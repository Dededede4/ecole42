/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_putstr_args.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mprevot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/24 18:56:59 by mprevot           #+#    #+#             */
/*   Updated: 2017/01/24 18:57:02 by mprevot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

size_t			ft_printf_putstr_printwidth(
	t_unicode *str, t_args *a)
{
	size_t		spaces;
	int			size;

	size = (int)ft_strsize(str);
	spaces = (a->width > size) ? a->width - size : 0;
	if (a->width != -1)
	{
		if (str[0] != 0 && a->precision != -1 &&
			(a->precision < size && a->type != 'u'))
			spaces = (a->width > a->precision) ? a->width - a->precision : 0;
		if (str[0] == 0 && a->type == 'c')
		{
			spaces--;
			a->width--;
		}
	}
	if (a->width != -1 && a->minus == -1)
		while (spaces--)
			ft_putchar((a->zero != -1) ? '0' : ' ');
	return (spaces);
}
