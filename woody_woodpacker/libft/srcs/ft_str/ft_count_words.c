/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_count_words.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heynard <heynard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/19 17:07:50 by heynard           #+#    #+#             */
/*   Updated: 2017/06/19 17:11:44 by heynard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"

int				ft_count_words(const char *str)
{
	int			ret;
	int			i;

	ret = 0;
	i = 0;
	if (!str)
		return (ret);
	while (str[i] != '\0')
	{
		while (ft_isspace(str[i++]))
			;
		if (str[i] != '\0')
		{
			ret++;
			while (!ft_isspace(str[i]) && str[i] != '\0')
				i++;
		}
	}
	return (ret);
}
