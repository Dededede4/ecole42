/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi_offt.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mprevot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/05 18:04:16 by mprevot           #+#    #+#             */
/*   Updated: 2019/03/05 18:04:17 by mprevot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "share.h"

off_t			ft_atoi_offt(const char *str)
{
	off_t		result;
	off_t		n;

	n = 0;
	while (*str == '\n' || *str == '\t' || *str == '\v' \
			|| *str == ' ' || *str == '\f' || *str == '\r')
		str++;
	if (*str == '+')
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
