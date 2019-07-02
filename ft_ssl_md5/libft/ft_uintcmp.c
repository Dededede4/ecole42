/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_uintcmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mprevot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/16 09:17:28 by mprevot           #+#    #+#             */
/*   Updated: 2018/02/16 09:17:30 by mprevot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_uintcmp(unsigned int *s1, unsigned int *s2)
{
	int i;

	if (!s1 || !s2)
		return (-1);
	i = 0;
	while (s1[i] == s2[i])
	{
		if (s1[i] == '\0')
			return (0);
		i++;
	}
	return ((int)((unsigned int)s1[i] - (unsigned int)s2[i]));
}
