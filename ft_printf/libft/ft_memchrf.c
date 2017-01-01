/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchrf.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mprevot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/28 12:37:58 by mprevot           #+#    #+#             */
/*   Updated: 2016/12/01 17:36:19 by mprevot          ###   ########.fr       */
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
			return s + i;
		i += 4;
	}
	return (NULL);
}
