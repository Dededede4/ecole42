/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_uintjoin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mprevot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/15 20:46:40 by mprevot           #+#    #+#             */
/*   Updated: 2018/02/15 20:46:49 by mprevot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

unsigned int		*ft_uintjoin(unsigned int const *s1, unsigned int const *s2)
{
	size_t			len1;
	size_t			len2;
	unsigned int	*new;

	if (s1 && !s2)
		return (ft_uintdup(s1));
	if (!s1 && s2)
		return (ft_uintdup(s2));
	if (!s1 || !s2)
		return (NULL);
	len1 = ft_uintlen(s1);
	len2 = ft_uintlen(s2);
	new = ft_uintnew(len1 + len2);
	if (new == NULL)
		return (NULL);
	ft_memcpy(new, (void*)(s1), len1 * 4);
	ft_memcpy(new + len1, (void*)(s2), len2 * 4);
	return (new);
}

unsigned int		*ft_uintjoin_multi(int autofree, ...)
{
	va_list			ap;
	unsigned int	*str;
	unsigned int	*strfree_arg;
	unsigned int	*strfree;

	va_start(ap, autofree);
	str = NULL;
	while ((strfree_arg = va_arg(ap, unsigned int *)))
	{
		strfree = str;
		str = ft_uintjoin(str, strfree_arg);
		free(strfree);
		if (autofree)
			free(strfree_arg);
	}
	va_end(ap);
	return (str);
}
