/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mprevot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/28 17:50:39 by mprevot           #+#    #+#             */
/*   Updated: 2016/12/02 16:22:24 by mprevot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

static size_t		ft_count_parts(char const *s, char c)
{
	size_t			i;
	size_t			count;

	i = 1;
	count = 0;
	if (s[0] != c)
		count++;
	while (s[i])
	{
		if (s[i - 1] == c && s[i] != c)
			count++;
		i++;
	}
	return (count);
}

static void			ft_get_parts(char const *s, char c, char **tab)
{
	t_parts_chars	v;

	v.i = 0;
	v.start = 0;
	v.count = 0;
	v.is_c = 1;
	while (s[v.i])
	{
		if (v.is_c && s[v.i] != c)
		{
			v.start = v.i;
			v.is_c = 0;
		}
		if (!v.is_c && s[v.i] == c)
		{
			tab[v.count] = ft_strsub(s, v.start, v.i - v.start);
			v.is_c = 1;
			v.count++;
		}
		if (!v.is_c && s[v.i + 1] == '\0')
		{
			tab[v.count] = ft_strsub(s, v.start, v.i - v.start + 1);
		}
		v.i++;
	}
}

char				**ft_strsplit(char const *s, char c)
{
	char			**tab;
	size_t			len;

	if (s == NULL || !c)
		return (NULL);
	len = ft_count_parts(s, c);
	tab = ft_memalloc(sizeof(tab) * (len + 1));
	if (tab == NULL)
		return (NULL);
	ft_get_parts(s, c, tab);
	return (tab);
}
