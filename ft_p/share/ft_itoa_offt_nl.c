/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa_offt_nl.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mprevot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/05 18:22:56 by mprevot           #+#    #+#             */
/*   Updated: 2019/03/05 18:22:57 by mprevot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "share.h"

char			*ft_itoa_offt_nl(off_t n)
{
	char		*str;
	int			len;

	len = ft_offtlen(n);
	str = ft_strnew(len + 1);
	str[len] = '\n';
	if (str == NULL)
		return (NULL);
	if (n < 0)
		str[0] = '-';
	else
		n = 0 - n;
	while (n / 10)
	{
		str[--len] = (0 - (n % 10)) + '0';
		n /= 10;
	}
	str[--len] = (0 - (n % 10)) + '0';

	return (str);
}
