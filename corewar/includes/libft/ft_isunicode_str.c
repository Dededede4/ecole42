/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isunicode_str.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mprevot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/25 16:15:58 by mprevot           #+#    #+#             */
/*   Updated: 2017/01/25 16:16:01 by mprevot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_bool		ft_isunicode_str(t_unicode *str)
{
	size_t	i;

	i = 0;
	if (!str)
		return (TRUE);
	while (str[i] != 0)
	{
		if (!ft_isunicode(str[i]))
		{
			return (FALSE);
		}
		i++;
	}
	return (TRUE);
}
