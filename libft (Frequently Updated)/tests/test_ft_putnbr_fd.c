/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_ft_putstr.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mprevot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/29 13:11:33 by mprevot           #+#    #+#             */
/*   Updated: 2016/11/29 14:14:09 by mprevot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"
#include <unistd.h>

int		main(void)
{
	int     out;
	int     p[2];
	char    sortie[100];

	out = dup(1);
	pipe(p);
	ft_putnbr_fd(42, p[1]);
	sortie[read(p[0], sortie, 100)] = '\0';
	if (0 != strcmp(sortie, "42"))
	{
		return (10);
	}

	out = dup(1);
	pipe(p);
	ft_putnbr_fd(-42, p[1]);
	sortie[read(p[0], sortie, 100)] = '\0';
	if (0 != strcmp(sortie, "-42"))
	{
		return (20);
	}

	out = dup(1);
	pipe(p);
	ft_putnbr_fd(-2147483648, p[1]);
	sortie[read(p[0], sortie, 100)] = '\0';
	if (0 != strcmp(sortie, "-2147483648"))
	{
		return (30);
	}
	return (0);

	out = dup(1);
	pipe(p);
	ft_putnbr_fd(2147483647, p[1]);
	sortie[read(p[0], sortie, 100)] = '\0';
	if (0 != strcmp(sortie, "-2147483648"))
	{
		return (40);
	}

	out = dup(1);
	pipe(p);
	ft_putnbr_fd(2147483647, p[1]);
	sortie[read(p[0], sortie, 100)] = '\0';
	if (0 != strcmp(sortie, "-2147483648"))
	{
		return (50);
	}
	return (0);
}
