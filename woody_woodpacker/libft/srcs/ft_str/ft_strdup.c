/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heynard <heynard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/18 17:43:12 by heynard           #+#    #+#             */
/*   Updated: 2018/12/24 17:57:58 by heynard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"

char			*ft_strdup(const char *s1)
{
	int			i;
	char		*result;

	i = 0;
	result = (char *)malloc(ft_strlen(s1) + 1);
	if (result)
	{
		while (s1[i] != '\0')
		{
			result[i] = s1[i];
			i++;
		}
		result[i] = '\0';
	}
	return (result);
}

static int		ft_strnlen(const char *s, int n)
{
	int			len;

	len = 0;
	while (s[len] != '\0' && len < n)
		len++;
	return (len);
}

char			*ft_strndup(const char *s1, int n)
{
	int			i;
	char		*result;

	i = 0;
	result = (char *)malloc(ft_strnlen(s1, n) + 1);
	if (result)
	{
		while (s1[i] != '\0' && i < n)
		{
			result[i] = s1[i];
			i++;
		}
		if (i == n)
			result[i++] = '\n';
		result[i] = '\0';
	}
	return (result);
}
