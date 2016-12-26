/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_ft_putchar.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mprevot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/29 12:29:01 by mprevot           #+#    #+#             */
/*   Updated: 2016/11/29 13:04:38 by mprevot          ###   ########.fr       */
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

	ft_putchar('G');
	sortie[read(p[0], sortie, 100)] = '\0';
	if (0 != strcmp(sortie, "G"))
	{
		dup2(out, 1);
		return (10);
	}

	dup2(out, 1);
	return (0);
}
