/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear_escapes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mprevot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/15 22:35:31 by mprevot           #+#    #+#             */
/*   Updated: 2018/02/15 22:35:33 by mprevot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../main.h"

unsigned int	*clear_escapes_startend(unsigned int **str)
{
	unsigned int	*cpy;
	unsigned int	*tmp;
	int				i;

	if ('\'' != (*str)[0] && '"' != (*str)[0])
	{
		tmp = ft_uintdup((*str));
		ft_memdel((void**)str);
		return (tmp);
	}
	i = 0;
	cpy = ft_uintdup((*str));
	while ((*str)[i + 1])
	{
		cpy[i] = (*str)[i + 1];
		i++;
	}
	cpy[i - 1] = '\0';
	ft_memdel((void**)str);
	return (cpy);
}

unsigned int	*clear_escapes(unsigned int *str)
{
	size_t		original_i;
	size_t		new_i;

	original_i = 0;
	new_i = 0;
	while (str[original_i])
	{
		if (!str[original_i + 1])
			break ;
		if ('\\' == str[original_i])
		{
			if ('\\' == str[original_i + 1] ||
				('"' == str[original_i + 1] && '\'' != str[0]) ||
				('\'' == str[original_i + 1] && '"' != str[0]))
			{
				original_i++;
			}
		}
		str[new_i] = str[original_i];
		original_i++;
		new_i++;
	}
	str[new_i] = str[original_i];
	str[new_i + 1] = '\0';
	return ((new_i > 2) ? clear_escapes_startend(&str) : (str));
}
