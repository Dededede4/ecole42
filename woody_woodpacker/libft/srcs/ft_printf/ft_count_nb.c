/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_count_nb.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heynard <heynard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/29 15:42:35 by heynard           #+#    #+#             */
/*   Updated: 2017/05/11 22:43:34 by heynard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"

int			ft_count_nb(intmax_t nb)
{
	int		nbc;

	nbc = 1;
	while (nb > 9)
	{
		nb /= 10;
		nbc++;
	}
	return (nbc);
}

int			ft_count_base_nb(intmax_t nb, int base)
{
	int		nbc;

	nbc = 1;
	while (nb > base - 1)
	{
		nb /= base;
		nbc++;
	}
	return (nbc);
}
