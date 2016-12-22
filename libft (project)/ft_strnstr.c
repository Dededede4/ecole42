/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mprevot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/27 10:29:52 by mprevot           #+#    #+#             */
/*   Updated: 2016/12/01 17:21:27 by mprevot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	len2;

	if (*little == '\0')
		return ((char *)big);
	len2 = ft_strlen(little);
	while (*big != '\0' && len-- >= len2)
	{
		if (*big == *little && ft_memcmp(big, little, len2) == 0)
			return ((char *)big);
		big++;
	}
	return (NULL);
}
