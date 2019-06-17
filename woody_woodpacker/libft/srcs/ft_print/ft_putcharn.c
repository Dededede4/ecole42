/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putcharn.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heynard <heynard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/24 15:07:54 by heynard           #+#    #+#             */
/*   Updated: 2017/04/24 15:14:48 by heynard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"

void		ft_putcharn(char *str, size_t len)
{
	size_t	i;

	i = 0;
	if (len == 0)
		return ;
	while (str[i] && i < len)
	{
		ft_putchar(str[i]);
		i++;
	}
}
