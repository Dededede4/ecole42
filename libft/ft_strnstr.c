/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mprevot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/27 10:29:52 by mprevot           #+#    #+#             */
/*   Updated: 2016/12/01 14:42:24 by mprevot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	strlen;
	size_t	i;
	int		cmp;

	if (!(*little))
		return ((char *)big);
	strlen = ft_strlen(little);
	if (strlen > ft_strlen(big))
		return (NULL);
	i = len - strlen + 2;
	cmp = -1;
	while (--i && *big && len-- >= strlen && cmp != 0)
	{
		cmp = ft_strncmp(big, little, strlen);
		if (cmp != 0)
			big++;
	}
	if (!*big || (cmp != 0 && i == 0))
		return (NULL);
	return ((char *)big);
}
