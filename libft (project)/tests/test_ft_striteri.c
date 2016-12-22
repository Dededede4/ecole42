/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_ft_striteri.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mprevot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/28 12:24:28 by mprevot           #+#    #+#             */
/*   Updated: 2016/11/28 12:33:06 by mprevot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

#include <stdio.h>

void	change(unsigned int i, char *c)
{
	(*c) = '0'+(char)i;
}

int		main(void)
{
	char	str[] = "abcd";
	char	cmp[] = "0123";

	ft_striteri(str, change);
	if (strcmp(str, cmp) != 0)
	{
		return (10);
	}
	return (0);
}
