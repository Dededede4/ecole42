/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi_uint.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mprevot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/16 09:19:12 by mprevot           #+#    #+#             */
/*   Updated: 2018/02/16 09:19:28 by mprevot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int			ft_atoi_uint(const unsigned int *str)
{
	int		result;
	int		n;

	n = 0;
	while (*str == '\n' || *str == '\t' || *str == '\v' \
			|| *str == ' ' || *str == '\f' || *str == '\r')
		str++;
	if (*str == '-')
	{
		n = 1;
		str++;
	}
	else if (*str == '+')
		str++;
	result = 0;
	while (*str && *str >= '0' && *str <= '9')
	{
		result = (result * 10) - (*str - '0');
		str++;
	}
	if (n)
		return (result);
	else
		return (0 - result);
}
