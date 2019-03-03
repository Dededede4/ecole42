/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_left.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mprevot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/17 21:27:29 by mprevot           #+#    #+#             */
/*   Updated: 2017/07/17 21:27:31 by mprevot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putstr_left(char const *s, size_t place)
{
	size_t	spaces;

	spaces = place - ft_strlen(s);
	while (*s)
		ft_putchar(*(s++));
	while (place && spaces--)
		ft_putchar(' ');
}
