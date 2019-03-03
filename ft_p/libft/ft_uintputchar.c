/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_uintputchar.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mprevot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/15 20:51:24 by mprevot           #+#    #+#             */
/*   Updated: 2018/02/15 20:51:31 by mprevot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void				ft_uintputchar(unsigned int const *str)
{
	unsigned char	*s;

	s = (unsigned char *)str;
	if (s[0] > 0)
		ft_putchar(s[0]);
	if (s[1] > 0)
		ft_putchar(s[1]);
	if (s[2] > 0)
		ft_putchar(s[2]);
	if (s[3] > 0)
		ft_putchar(s[3]);
}
