/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heynard <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/25 15:27:04 by heynard           #+#    #+#             */
/*   Updated: 2016/12/14 18:36:52 by heynard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"

char		*ft_strjoin(char const *s1, char const *s2)
{
	char	*str;
	int		len;

	s1 = (s1 == NULL) ? "" : s1;
	s2 = (s2 == NULL) ? "" : s2;
	if (s1 && s2)
	{
		len = ft_strlen(s1) + ft_strlen(s2);
		str = (char *)malloc((len + 1) * sizeof(char));
		if (str != NULL)
		{
			str = ft_strcpy(str, s1);
			str = ft_strcat(str, s2);
			return (str);
		}
	}
	return (NULL);
}
