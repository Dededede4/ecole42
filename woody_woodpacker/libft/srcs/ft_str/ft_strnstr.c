/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heynard <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/18 19:35:17 by heynard           #+#    #+#             */
/*   Updated: 2016/11/28 16:36:25 by heynard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"

char		*ft_strnstr(const char *big, const char *l, size_t n)
{
	size_t	i;
	size_t	j;

	if (*l == '\0')
		return ((char*)big);
	i = 0;
	while (i < n && big[i] != '\0')
	{
		if (big[i] == *l)
		{
			j = 0;
			while (i + j < n && l[j] == big[i + j])
			{
				j++;
				if (l[j] == '\0')
					return ((char *)&big[i]);
			}
		}
		i++;
	}
	return (NULL);
}
