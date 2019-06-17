/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin_spec.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heynard <heynard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/22 17:32:46 by heynard           #+#    #+#             */
/*   Updated: 2017/06/22 17:40:25 by heynard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"

char		*ft_strjoin_spec(char const *s1, char const *s2, char sp)
{
	char	*str;
	int		len;

	s1 = (s1 == NULL) ? "" : s1;
	s2 = (s2 == NULL) ? "" : s2;
	if (s1 && s2)
	{
		len = ft_strlen_spec(s1, sp) + ft_strlen(s2);
		str = (char *)malloc((len + 1) * sizeof(char));
		if (str != NULL)
		{
			str = ft_strcpy2_spec(str, s1, sp);
			str = ft_strcat(str, s2);
			return (str);
		}
	}
	return (NULL);
}
