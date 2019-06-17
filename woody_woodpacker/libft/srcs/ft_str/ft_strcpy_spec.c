/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcpy_spec.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heynard <heynard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/20 13:52:21 by heynard           #+#    #+#             */
/*   Updated: 2017/06/21 15:09:35 by heynard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"

char			*ft_strcpy_spec(char *str, char spec)
{
	char		*new;
	int			i;

	if ((new = (char *)malloc(sizeof(char) * ft_strlen_spec(str, spec) + 1))
							== NULL)
		return (NULL);
	i = 0;
	while (str[i] != spec && str[i] != '\0')
	{
		new[i] = str[i];
		i++;
	}
	new[i] = '\0';
	return (new);
}
