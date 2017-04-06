/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_execarg2.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mprevot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/23 18:09:23 by mprevot           #+#    #+#             */
/*   Updated: 2017/01/23 18:09:27 by mprevot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int					ft_printf_execarg_percent(t_args *a)
{
	unsigned char	c;
	t_unicode		*s;

	c = '%';
	a->precision = -1;
	s = ft_wstrdup((unsigned char*)(&c), 1);
	if (!s)
		return (-1);
	ft_printf_wputstr(s, a, ft_putstr_ascii);
	free(s);
	return (1);
}
