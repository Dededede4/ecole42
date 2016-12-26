/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_ft_strlcat.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mprevot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/14 19:09:16 by mprevot           #+#    #+#             */
/*   Updated: 2016/12/01 18:33:50 by mprevot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"
#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <unistd.h>

int		main(void)
{
	char	s1[50] = "OualalalalaPO";
	char	s2[] = "Pooow";
	size_t	val;

	char    d1[50] = "OualalalalaPO";
	char    d2[] = "Pooow";
	size_t	val2;

	val = strlcat(s1, s2, 4);
	val2 = ft_strlcat(d1, d2, 4);
	if (val != val2)
		return (10);

	if (strcmp(d1, s1) != 0)
		return (20);

	char    s3[50] = "OualalalalaPO";
	char    s4[] = "Pooow";
	size_t  val3;

	char    d3[50] = "OualalalalaPO";
	char    d4[] = "Pooow";
	size_t  val4;

	val3 = strlcat(s3, s4, 50);
	val4 = ft_strlcat(d3, d4, 50);
	if (val3 != val4)
		return (30);

	return (0);
}
