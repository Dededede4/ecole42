/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup_len.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mprevot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/06 12:14:38 by mprevot           #+#    #+#             */
/*   Updated: 2017/08/06 12:14:49 by mprevot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*ft_strdup_len(char *str, size_t len)
{
	char	*newstr;

	newstr = ft_strnew(len);
	ft_memcpy(newstr, str, len);
	return (newstr);
}
