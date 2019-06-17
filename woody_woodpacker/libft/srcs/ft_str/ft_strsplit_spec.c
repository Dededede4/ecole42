/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit_spec.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heynard <heynard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/25 15:09:23 by heynard           #+#    #+#             */
/*   Updated: 2017/06/24 14:04:32 by heynard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"

static int			ft_sizeofsplit(const char *s, char c, char spec)
{
	int				i;
	int				ret;

	ret = 0;
	i = 0;
	if (s == NULL)
		return (0);
	while (s[i] != '\0' && s[i] != spec)
	{
		if (s[i] == c)
		{
			while (s[i] == c)
				i++;
		}
		else
		{
			while (s[i] != c && s[i] != '\0' && s[i] != spec)
				i++;
			ret++;
		}
	}
	return (ret);
}

static char			**ft_split(const char *s, char c, char **tab, char spec)
{
	unsigned int	i;
	unsigned int	j;
	unsigned int	start;

	i = 0;
	j = 0;
	if (s == NULL)
		return (tab);
	while (s[i] != '\0' && s[i] != spec)
	{
		if (s[i] == c || s[i] == '\t')
			while (s[i] == c || s[i] == '\t')
				i++;
		else
		{
			start = i;
			while (s[i] != c && s[i] != '\0' && s[i] != spec)
				i++;
			tab[j] = ft_strsub(s, start, i - start);
			j++;
		}
		tab[j] = NULL;
	}
	return (tab);
}

char				**ft_strsplit_spec(char const *s, char c, char spec)
{
	char			**tab;
	int				i;

	i = 0;
	if (!s)
		return (NULL);
	while (*(s + i) == ' ' || *(s + i) == '\t')
		i++;
	if (*(s + i) == '\0' || *(s + i) == spec)
		return (NULL);
	tab = (char **)malloc(sizeof(char *) * ft_sizeofsplit(s, c, spec) + 1);
	if (tab == NULL)
	{
		ft_printf("minishell: Memory allocation failed in ft_strsplit\n");
		return (NULL);
	}
	if (s == NULL)
		return (tab);
	tab = ft_split(s, c, tab, spec);
	return (tab);
}
