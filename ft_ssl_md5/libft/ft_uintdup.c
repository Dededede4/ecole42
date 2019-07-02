/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_uintdup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mprevot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/15 20:52:44 by mprevot           #+#    #+#             */
/*   Updated: 2018/02/15 20:52:54 by mprevot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

unsigned int		*ft_uintdup(unsigned int const *s1)
{
	unsigned int	*s2;
	size_t			len;

	len = ft_uintlen(s1) + 1;
	s2 = ft_memalloc((sizeof(*s2) * len));
	if (!s2)
		return (NULL);
	ft_memcpy(s2, s1, sizeof(*s2) * len);
	return (s2);
}
