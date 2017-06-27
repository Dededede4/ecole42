/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isascii_str.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mprevot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/25 16:14:32 by mprevot           #+#    #+#             */
/*   Updated: 2017/01/25 16:14:35 by mprevot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_bool		ft_isascii_str(unsigned char *str)
{
	size_t	i;

	i = 0;
	if (!str)
		return (TRUE);
	while (str[i])
	{
		if (!ft_isascii(str[i]))
			return (FALSE);
		i++;
	}
	return (TRUE);
}
