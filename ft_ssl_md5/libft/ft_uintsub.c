/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_uintsub.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mprevot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/15 20:38:29 by mprevot           #+#    #+#             */
/*   Updated: 2018/02/15 20:38:50 by mprevot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

unsigned int	*ft_uintsub(
	unsigned int const *s, unsigned int start, size_t len)
{
	unsigned int	*str;

	if (!s)
		return (NULL);
	str = ft_uintnew(len);
	if (str == NULL)
		return (NULL);
	ft_memcpy(str, (void*)(s + start), len * 4);
	return (str);
}
