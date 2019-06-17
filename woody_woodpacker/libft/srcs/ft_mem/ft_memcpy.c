/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heynard <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/12 16:08:36 by heynard           #+#    #+#             */
/*   Updated: 2016/11/25 13:52:06 by heynard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"

void				*ft_memcpy(void *dst, const void *src, size_t n)
{
	unsigned char	*str_dst;
	unsigned char	*str_src;
	size_t		i;

	str_dst = (unsigned char *)dst;
	str_src = (unsigned char *)src;
	i = -1;
	while (++i < n)
		*(str_dst + i) = *(str_src + i);
	return (dst);
}
