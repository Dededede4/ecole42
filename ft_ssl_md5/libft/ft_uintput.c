/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_uintput.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mprevot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/15 20:52:06 by mprevot           #+#    #+#             */
/*   Updated: 2018/02/15 20:52:15 by mprevot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void				ft_uintput(unsigned int *str)
{
	size_t			y;
	unsigned char	*s;

	if (NULL == str)
		return ;
	s = (unsigned char *)str;
	y = 0;
	while (str[y])
	{
		ft_uintputchar(str + y);
		y++;
	}
}
