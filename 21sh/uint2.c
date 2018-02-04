/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   uint2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mprevot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/04 09:24:06 by mprevot           #+#    #+#             */
/*   Updated: 2018/02/04 09:24:08 by mprevot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

unsigned int		*ft_uintnew(size_t size)
{
	return (ft_memalloc((size + 1) * 4));
}

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

unsigned int		*ft_uintjoin_multi(t_bool autofree, ...)
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

unsigned int		*ft_uintdup_len(unsigned int *str, size_t len)
{
	unsigned int	*newstr;

	newstr = ft_uintnew(len);
	ft_memcpy(newstr, str, len * 4);
	return (newstr);
}

char				*ft_uint_to_char(unsigned int *input)
{
	unsigned char	*s;
	size_t			i;
	size_t			i_output;
	char			*o;

	o = ft_strnew(ft_uintlen(input) * 4);
	i = 0;
	i_output = 0;
	while (input[i])
	{
		s = input + i;
		if (s[0] > 0)
			o[i_output++] = s[0];
		if (s[1] > 0)
			o[i_output++] = s[1];
		if (s[2] > 0)
			o[i_output++] = s[2];
		if (s[3] > 0)
			o[i_output++] = s[3];
		i++;
	}
	return (o);
}
