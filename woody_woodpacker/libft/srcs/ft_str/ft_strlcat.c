/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heynard <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/18 18:22:07 by heynard           #+#    #+#             */
/*   Updated: 2016/11/25 13:52:36 by heynard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"

size_t		ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	i;

	i = 0;
	while (dst[i])
	{
		i++;
		if (i > size)
			return (size + ft_strlen(src));
	}
	while (*src && i < size - 1)
	{
		dst[i] = *src;
		src += 1;
		i++;
	}
	dst[i] = '\0';
	return (ft_strlen((const char *)dst) + ft_strlen(src));
}
