/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ncurses_put_background.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntoniolo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/20 16:31:59 by ntoniolo          #+#    #+#             */
/*   Updated: 2017/03/27 14:42:55 by ntoniolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void		ncurses_put_background(t_datas *datas, int pc,
												char champion, int size)
{
	int i;

	if (pc < 0)
		pc += MEM_SIZE;
	i = 0;
	while (i < size)
	{
		datas->nc.background[(pc + i) % MEM_SIZE] = champion;
		datas->nc.light[(pc + i) % MEM_SIZE] = 40;
		i++;
	}
}
