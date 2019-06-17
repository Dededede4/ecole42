/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_count_words_spec.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heynard <heynard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/19 17:19:29 by heynard           #+#    #+#             */
/*   Updated: 2017/06/27 21:38:39 by heynard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"

int				ft_count_words_spec(const char *str, char spec)
{
	int			ret;
	int			i;

	ret = 0;
	i = 0;
	if (!str)
		return (ret);
	while (str[i] != '\0' && str[i] != spec)
	{
		while (ft_isspace(str[i]))
			i++;
		if (str[i] != '\0' && str[i] != spec)
		{
			ret++;
			while (!ft_isspace(str[i]) && str[i] != '\0' && str[i] != spec)
				i++;
		}
	}
	return (ret);
}
