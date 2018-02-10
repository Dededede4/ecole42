/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   uint1.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mprevot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/04 09:23:55 by mprevot           #+#    #+#             */
/*   Updated: 2018/02/04 09:23:57 by mprevot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

size_t				ft_uintlen(unsigned int const *s)
{
	size_t		i;

	if (NULL == s)
		return (0);
	i = 0;
	while (s[i])
		i++;
	return (i);
}

void				ft_uintputchar(unsigned int const *str)
{
	unsigned char	*s;

	s = (unsigned char *)str;
	if (s[0] > 0)
		ft_putchar(s[0]);
	if (s[1] > 0)
		ft_putchar(s[1]);
	if (s[2] > 0)
		ft_putchar(s[2]);
	if (s[3] > 0)
		ft_putchar(s[3]);
}

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

void				ft_uintdel(unsigned int **as)
{
	ft_memdel((void *)as);
}
