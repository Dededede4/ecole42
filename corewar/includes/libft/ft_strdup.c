/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mprevot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/14 16:17:53 by mprevot           #+#    #+#             */
/*   Updated: 2016/12/01 14:13:09 by mprevot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s1)
{
	char	*s2;
	int		len;

	len = ft_strlen(s1) + 1;
	s2 = ft_memalloc((sizeof(*s2) * len));
	if (!s2)
		return (NULL);
	ft_memcpy(s2, s1, len);
	return (s2);
}
