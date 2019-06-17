/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heynard <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/18 19:23:31 by heynard           #+#    #+#             */
/*   Updated: 2016/11/18 19:34:41 by heynard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"

char		*ft_strstr(const char *big, const char *little)
{
	size_t	size;

	if (*little == '\0')
		return ((char *)big);
	while (*big)
	{
		if (*big == *little)
		{
			size = 0;
			while (big[size] == little[size])
			{
				size++;
				if (little[size] == '\0')
					return ((char *)big);
			}
		}
		big += 1;
	}
	return (NULL);
}
