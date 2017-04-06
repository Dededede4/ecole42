/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   random.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntoniolo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/27 23:02:42 by ntoniolo          #+#    #+#             */
/*   Updated: 2017/03/27 23:05:27 by ntoniolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "script.h"

int		rd(t_rand *rd)
{
	int i;
	int index;
	int rn;

	if (rd->first == 0)
	{
		srand(time(NULL));
		i = 0;
		while (i < N)
		{
			rd->tab[i] = rand();
			i++;
		}
		rd->first = 1;
	}
	index = (int)(rand() / (double)RAND_MAX * (N - 1));
	rn = rd->tab[index];
	rd->tab[index] = rand();
	return (rn);
}
