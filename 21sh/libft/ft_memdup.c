/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mprevot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/13 22:43:06 by mprevot           #+#    #+#             */
/*   Updated: 2018/02/13 22:43:24 by mprevot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*ft_memdup(char *mem, size_t len)
{
	char	*newalloc;
	size_t	i;

	i = 0;
	newalloc = ft_memalloc(len + 4);
	while (i < len)
	{
		newalloc[i] = mem[i];
		i++;
	}
	return (newalloc);
}
