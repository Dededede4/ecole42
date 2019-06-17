/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putcharn_fd.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heynard <heynard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/24 15:13:24 by heynard           #+#    #+#             */
/*   Updated: 2017/04/24 15:14:36 by heynard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"

void		ft_putcharn_fd(char *str, size_t len, int fd)
{
	size_t	i;

	i = 0;
	if (len == 0)
		return ;
	while (str[i] && i < len)
	{
		ft_putchar_fd(str[i], fd);
		i++;
	}
}
