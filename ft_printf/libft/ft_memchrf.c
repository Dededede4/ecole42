/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchrf.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mprevot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/23 19:05:07 by mprevot           #+#    #+#             */
/*   Updated: 2017/01/23 19:05:18 by mprevot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void		*ft_memchrf(void *s, int (*f)(void *), size_t len)
{
	size_t	i;

	i = 0;
	if (!s || !f)
		return (NULL);
	while (i < len)
	{
		if (f(s + i))
			return (s + i);
		i += 4;
	}
	return (NULL);
}
