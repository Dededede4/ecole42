/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mprevot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/14 19:03:44 by mprevot           #+#    #+#             */
/*   Updated: 2016/11/15 12:44:02 by mprevot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *restrict dst, const char *restrict src, size_t size)
{
	size_t	i;
	size_t	len;

	len = 0;
	i = 0;
	while (len < size && dst[len])
		len++;
	if (len == size)
		return (len + ft_strlen(src));
	while (src[i])
	{
		if (i < len)
		{
			dst[i] = src[i];
		}
		i++;
	}
	dst[i] = '\0';
	return (len + i);
}
