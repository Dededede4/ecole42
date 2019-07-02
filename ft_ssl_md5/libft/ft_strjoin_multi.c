/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin_multi.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mprevot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/17 14:38:27 by mprevot           #+#    #+#             */
/*   Updated: 2017/02/17 14:38:30 by mprevot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin_multi(int autofree, ...)
{
	va_list			ap;
	char			*str;
	char			*strfree_arg;
	char			*strfree;

	va_start(ap, autofree);
	str = NULL;
	while ((strfree_arg = va_arg(ap, char *)))
	{
		strfree = str;
		str = ft_strjoin(str, strfree_arg);
		free(strfree);
		if (autofree)
			free(strfree_arg);
	}
	va_end(ap);
	return (str);
}
