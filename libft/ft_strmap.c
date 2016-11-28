/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mprevot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/28 12:37:58 by mprevot           #+#    #+#             */
/*   Updated: 2016/11/28 12:56:41 by mprevot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmap(char const *s, char (*f)(char))
{
	char	*dup;
	size_t	i;

	i = 0;
	dup = ft_strdup(s);
	while (dup[i])
	{
		dup[i] = f(dup[i]);
		i++;
	}
	return (dup);
}
