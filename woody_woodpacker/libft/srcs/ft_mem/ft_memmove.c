/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heynard <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/12 16:34:50 by heynard           #+#    #+#             */
/*   Updated: 2016/11/28 15:25:28 by heynard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"

static void			*ft_memcpy_revers(void *dst, const void *src, size_t n)
{
	unsigned char	*str_dst;
	unsigned char	*str_src;

	str_dst = (unsigned char *)dst;
	str_src = (unsigned char *)src;
	while (n--)
		*(str_dst + n) = *(str_src + n);
	return (dst);
}

void				*ft_memmove(void *dst, const void *src, size_t len)
{
	if (dst == src)
		return (dst);
	if (dst < src)
		dst = ft_memcpy(dst, src, len);
	if (dst > src)
		dst = ft_memcpy_revers(dst, src, len);
	return (dst);
}
