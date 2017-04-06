/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mprevot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/11 11:56:12 by mprevot           #+#    #+#             */
/*   Updated: 2016/11/11 14:45:56 by mprevot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *s1, const void *s2, size_t n)
{
	void		*ret;

	ret = s1;
	if (s1 < s2)
		while ((size_t)(s1 - ret) < n)
			*(unsigned char *)s1++ = *(unsigned char *)s2++;
	else
		while (n-- > 0)
			((unsigned char *)s1)[n] = ((unsigned char *)s2)[n];
	return (ret);
}
