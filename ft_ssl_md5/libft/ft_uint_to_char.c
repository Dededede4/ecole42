/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_uint_to_char.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mprevot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/15 20:48:39 by mprevot           #+#    #+#             */
/*   Updated: 2018/02/15 20:48:50 by mprevot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char				*ft_uint_to_char(unsigned int *input)
{
	unsigned char	*s;
	size_t			i;
	size_t			i_output;
	char			*o;

	o = ft_strnew(ft_uintlen(input) * 4);
	i = 0;
	i_output = 0;
	while (input[i])
	{
		s = (unsigned char*)(input + i);
		if (s[0] > 0)
			o[i_output++] = s[0];
		if (s[1] > 0)
			o[i_output++] = s[1];
		if (s[2] > 0)
			o[i_output++] = s[2];
		if (s[3] > 0)
			o[i_output++] = s[3];
		i++;
	}
	return (o);
}
