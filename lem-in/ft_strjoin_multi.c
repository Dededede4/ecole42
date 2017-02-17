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

#include "lemin.h"

char	*ft_strjoin_multi(t_bool autofree, ...)
{
	va_list			ap;
	char			*str;
	char			*strfree;

	va_start(ap, autofree);
	str = NULL;
	while ((strfree = va_arg(ap, char *)))
	{
		str = ft_strjoin(str, strfree);
		if (autofree)
			free(strfree);
	}
	va_end(ap);
	return (str);
}
