/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ft_square_root.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntoniolo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/13 15:46:32 by ntoniolo          #+#    #+#             */
/*   Updated: 2017/03/13 15:46:49 by ntoniolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

int			ft_square_root(int square)
{
	int		i;

	i = 1;
	while (i < square)
	{
		if (i * i == square)
			return (i);
		if (i * i > square)
			return (i - 1);
		++i;
	}
	return (0);
}
