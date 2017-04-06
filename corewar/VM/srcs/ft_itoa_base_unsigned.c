/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa_base_unsigned.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gnebie <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/30 04:52:36 by gnebie            #+#    #+#             */
/*   Updated: 2016/11/30 04:52:39 by gnebie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

static long			count_uintmax(uintmax_t n, uintmax_t base)
{
	long	i;

	if (n == 0)
		return (1);
	i = 0;
	while (n != 0)
	{
		i++;
		n = n / base;
	}
	return (i);
}

char				*ft_itoa_base_unsigned_max(uintmax_t n, int base, char a)
{
	char	*number;
	long	i;
	long	j;

	if (base < 2 || base > 16)
		return (NULL);
	i = count_uintmax(n, (uintmax_t)base);
	if (!(number = ft_memalloc(sizeof(char) * (size_t)(i + 1))))
		return (NULL);
	number[i--] = 0;
	if (n == 0)
		number[i] = '0';
	while (n != 0)
	{
		if ((j = (long)n % (long)base) < 0)
			j = j * -1;
		(j < 10) ? (number[i] = (char)(j + '0')) :
					(number[i] = (char)(j + a - 10));
		n = n / (uintmax_t)base;
		i--;
	}
	return (number);
}
