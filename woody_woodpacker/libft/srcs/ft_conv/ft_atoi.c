/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heynard <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/25 13:32:25 by heynard           #+#    #+#             */
/*   Updated: 2017/04/01 11:43:56 by heynard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"

int			ft_atoi(const char *str)
{
	int		neg;
	int		ret;
	int		i;

	i = 0;
	neg = 1;
	ret = 0;
	while (*(str + i) == ' ' ||
			*(str + i) == '\n' ||
			*(str + i) == '\t' ||
			*(str + i) == '\r' ||
			*(str + i) == '\v' ||
			*(str + i) == '\f')
		i++;
	if (*(str + i) == '-')
		neg = -1;
	if (*(str + i) == '-' || *(str + i) == '+')
		i++;
	while (ft_isdigit(*(str + i)))
	{
		ret = ret * 10 + (*(str + i) - '0');
		i++;
	}
	return (ret * neg);
}
