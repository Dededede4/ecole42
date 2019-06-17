/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heynard <heynard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/26 14:32:32 by heynard           #+#    #+#             */
/*   Updated: 2017/04/26 15:05:54 by heynard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"

char		*ft_itoa_base(int value, int base)
{
	char	*str;
	int		neg;
	int		i;

	neg = 0;
	i = 1;
	if (value < 0)
	{
		if (base == 10)
			neg = 1;
		value *= -1;
	}
	while (ft_power(base, i) - 1 < value)
		i++;
	str = (char *)malloc(sizeof(char) * i);
	str[i + neg] = '\0';
	while (i-- > 0)
	{
		str[i + neg] = (value % base) + (value % base > 9 ? 'A' - 10 : '0');
		value /= base;
	}
	if (neg)
		str[0] = '-';
	return (str);
}
