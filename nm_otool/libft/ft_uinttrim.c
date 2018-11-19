/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_uinttrim.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mprevot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/15 20:39:43 by mprevot           #+#    #+#             */
/*   Updated: 2018/02/15 20:39:45 by mprevot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

unsigned int		*ft_uinttrim(unsigned int const *s)
{
	size_t	d;
	size_t	f;

	if (!s)
		return (NULL);
	d = 0;
	while (s[d] == ' ' || s[d] == '\t' || s[d] == '\n')
		d++;
	if (s[d] == '\0')
		return (ft_uintnew(0));
	f = ft_uintlen(s) - 1;
	while (s[f] == ' ' || s[f] == '\t' || s[f] == '\n')
		f--;
	return (ft_uintsub(s, d, f - d + 1));
}

unsigned int		*ft_uinttrim_free(unsigned int **str)
{
	unsigned int	*tmp;

	tmp = ft_uinttrim(*str);
	ft_memdel((void**)str);
	return (tmp);
}
