/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mprevot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/15 13:37:55 by mprevot           #+#    #+#             */
/*   Updated: 2016/11/15 14:10:25 by mprevot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strstr(const char *big, const char *little)
{
	size_t	len;

	if (!(*little))
		return ((char *)big);
	len = ft_strlen(little);
	while (*big && ft_strncmp(big, little, len) != 0)
	{
		big++;
	}
	if (!*big)
		return (NULL);
	return ((char *)big);
}
