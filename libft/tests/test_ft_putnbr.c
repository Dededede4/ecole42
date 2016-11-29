/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_ft_putstr.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mprevot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/29 13:11:33 by mprevot           #+#    #+#             */
/*   Updated: 2016/11/29 13:42:36 by mprevot          ###   ########.fr       */
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
	dup2(p[1], 1);
	ft_putnbr(42);
	sortie[read(p[0], sortie, 100)] = '\0';
	if (0 != strcmp(sortie, "42"))
	{
		dup2(out, 1);
		return (10);
	}
	dup2(out, 1);

	out = dup(1);
	pipe(p);
	dup2(p[1], 1);
	ft_putnbr(-42);
	sortie[read(p[0], sortie, 100)] = '\0';
	if (0 != strcmp(sortie, "-42"))
	{
		dup2(out, 1);
		return (20);
	}
	dup2(out, 1);

	out = dup(1);
	pipe(p);
	dup2(p[1], 1);
	ft_putnbr(-2147483648);
	sortie[read(p[0], sortie, 100)] = '\0';
	if (0 != strcmp(sortie, "-2147483648"))
	{
		dup2(out, 1);
		return (30);
	}
	dup2(out, 1);
	return (0);

	out = dup(1);
	pipe(p);
	dup2(p[1], 1);
	ft_putnbr(2147483647);
	sortie[read(p[0], sortie, 100)] = '\0';
	if (0 != strcmp(sortie, "-2147483648"))
	{
		dup2(out, 1);
		return (40);
	}
	dup2(out, 1);

	out = dup(1);
	pipe(p);
	dup2(p[1], 1);
	ft_putnbr(2147483647);
	sortie[read(p[0], sortie, 100)] = '\0';
	if (0 != strcmp(sortie, "-2147483648"))
	{
		dup2(out, 1);
		return (50);
	}
	dup2(out, 1);
	return (0);
}
