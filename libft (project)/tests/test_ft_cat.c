/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_ft_putstr.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mprevot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/29 13:11:33 by mprevot           #+#    #+#             */
/*   Updated: 2016/12/02 20:27:18 by mprevot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"
#include <unistd.h>

int		main(void)
{
	int     out;
	int     p[2];
	char    sortie[100];
	char	str[] = "you win\n";

	out = dup(1);
	pipe(p);
	dup2(p[1], 1);

	ft_cat("testfile");
	sortie[read(p[0], sortie, 100)] = '\0';
	if (0 != strcmp(sortie, str))
	{
		dup2(out, 1);
		return (10);
	}

	dup2(out, 1);
	return (0);
}
