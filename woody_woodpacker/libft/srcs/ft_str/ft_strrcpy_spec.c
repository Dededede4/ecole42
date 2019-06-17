/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrcpy_spec.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heynard <heynard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/21 15:01:03 by heynard           #+#    #+#             */
/*   Updated: 2017/06/21 15:09:42 by heynard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"

char				*ft_strrcpy_spec(const char *str, char spec)
{
	int				i;
	int				j;
	char			*ret;

	if ((ret = (char *)malloc(sizeof(char) * ft_strrlen_spec(str, spec) + 1))
							== NULL)
		return (NULL);
	i = 0;
	j = 0;
	while (str[i] != '\0' && str[i] != spec)
		i++;
	if (str[i] == '\0')
	{
		free(ret);
		return (NULL);
	}
	i++;
	while (str[i] != '\0')
	{
		ret[j] = str[i];
		j++;
		i++;
	}
	ret[j] = '\0';
	return (ret);
}
