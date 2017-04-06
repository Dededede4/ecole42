/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isatoied.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gnebie <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/27 19:10:08 by gnebie            #+#    #+#             */
/*   Updated: 2017/02/27 19:10:09 by gnebie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "corewar.h"

int			ft_isatoied(char *str)
{
	long	test;
	int		signe;

	test = 0;
	signe = 1;
	while ((*str < 14 && *str > 8) || *str == 32)
		++str;
	if (*str == '-' || *str == '+')
		if ('-' == *(str++))
			signe = -1;
	if (!*str)
		return (-1);
	while (ft_isdigit(*str))
	{
		test = test * 10 + (*str - '0');
		++str;
		if (test > INT_MAX || (signe == -1 && test > (long)INT_MAX + 1))
			return (-1);
	}
	if (!*str)
		return (1);
	return (-1);
}
