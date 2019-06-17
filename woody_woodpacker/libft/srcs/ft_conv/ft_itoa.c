/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heynard <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/25 14:18:44 by heynard           #+#    #+#             */
/*   Updated: 2016/11/29 15:09:30 by heynard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"

static void		ft_negative(int *n, int *neg)
{
	if (*n < 0)
	{
		*n *= -1;
		*neg = 1;
	}
}

char			*ft_itoa(int n)
{
	int			tmp;
	int			len;
	int			neg;
	char		*ret;

	if (n == -2147483648)
		return (ft_strdup("-2147483648"));
	tmp = n;
	len = 2;
	neg = 0;
	ft_negative(&n, &neg);
	while (tmp /= 10)
		len++;
	len += neg;
	if ((ret = (char *)malloc(sizeof(char) * len)) == NULL)
		return (NULL);
	ret[--len] = '\0';
	while (len--)
	{
		ret[len] = n % 10 + '0';
		n = n / 10;
	}
	if (neg)
		ret[0] = '-';
	return (ret);
}
