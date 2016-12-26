/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_ft_striter.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mprevot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/28 12:09:50 by mprevot           #+#    #+#             */
/*   Updated: 2016/11/28 12:20:23 by mprevot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

void	add_one(char *c)
{
	(*c)++;
}

int		main(void)
{
	char	str[] = "abcd";
	char	cmp[] = "bcde";

	ft_striter(str, add_one);
	if (strcmp(str, cmp) != 0)
	{
		return (10);
	}
	return (0);
}
