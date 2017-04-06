/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ncurses_light.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntoniolo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/20 17:24:30 by ntoniolo          #+#    #+#             */
/*   Updated: 2017/03/20 17:27:43 by ntoniolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void		ncurses_light(t_datas *datas)
{
	int i;

	i = 0;
	while (i < MEM_SIZE)
	{
		if (datas->nc.light[i] > 0)
			datas->nc.light[i]--;
		i++;
	}
}
