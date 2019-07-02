/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_uintdup_len.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mprevot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/15 20:47:37 by mprevot           #+#    #+#             */
/*   Updated: 2018/02/15 20:47:51 by mprevot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

unsigned int		*ft_uintdup_len(unsigned int *str, size_t len)
{
	unsigned int	*newstr;

	newstr = ft_uintnew(len);
	ft_memcpy(newstr, str, len * 4);
	return (newstr);
}
