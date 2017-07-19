/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_right.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mprevot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/17 21:26:16 by mprevot           #+#    #+#             */
/*   Updated: 2017/07/17 21:26:17 by mprevot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr_right(int nbr, size_t place)
{
	size_t	spaces;

	spaces = place - ft_intlen(nbr);
	while (place && spaces--)
		ft_putchar(' ');
	ft_putnbr(nbr);
}
