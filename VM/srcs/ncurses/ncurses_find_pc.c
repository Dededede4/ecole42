/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ncurses_find.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntoniolo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/20 17:56:12 by ntoniolo          #+#    #+#             */
/*   Updated: 2017/03/27 14:40:53 by ntoniolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void		ncurses_find_pc(t_datas *datas, t_draw *d)
{
	t_process	*pros;
	int			min;

	min = MEM_SIZE * 8;
	pros = datas->begin_process;
	while (pros)
	{
		if (pros->pc < min && pros->pc > d->max)
		{
			min = pros->pc;
			d->save_pros = pros->pc;
		}
		pros = pros->next;
	}
	if (d->save_pros >= 0)
		d->max = d->save_pros;
}
