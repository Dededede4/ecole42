/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ncurses_loop_arene.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntoniolo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/20 17:49:42 by ntoniolo          #+#    #+#             */
/*   Updated: 2017/03/27 15:12:44 by ntoniolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

static void		ncurses_option_print(t_datas *datas, t_draw *d, int i)
{
	if (d->cur_champ != (int)datas->nc.background[i])
	{
		wattroff(datas->nc.win, COLOR_PAIR(d->cur_champ) | WA_BOLD);
		d->highlight = 0;
		d->cur_champ = (int)datas->nc.background[i];
		if (d->cur_champ != 0)
			wattron(datas->nc.win, COLOR_PAIR(d->cur_champ));
	}
	if (d->highlight && datas->nc.light[i] <= 0)
	{
		wattroff(datas->nc.win, WA_BOLD);
		d->highlight = 0;
	}
	else if (!d->highlight && datas->nc.light[i] > 0)
	{
		wattron(datas->nc.win, WA_BOLD);
		d->highlight = 1;
	}
}

static void		ncurses_show_arene_element(t_datas *datas, t_draw *d, char elem)
{
	char		line[3];

	line[2] = 0;
	line[1] = (unsigned char)elem % 16;
	line[0] = ((unsigned char)elem / 16) % 16;
	line[0] += (line[0] >= 10) ? ('a' - 10) : ('0');
	line[1] += (line[1] >= 10) ? ('a' - 10) : ('0');
	if (d->count == d->save_pros)
	{
		mvwaddch(datas->nc.win, d->y, d->x, line[0] | A_REVERSE);
		mvwaddch(datas->nc.win, d->y, d->x + 1, line[1] | A_REVERSE);
		ncurses_find_pc(datas, d);
	}
	else
	{
		mvwaddch(datas->nc.win, d->y, d->x, line[0]);
		mvwaddch(datas->nc.win, d->y, d->x + 1, line[1]);
	}
	d->count++;
}

void			ncurses_loop_arene(t_datas *datas, t_draw *d)
{
	int		i;

	i = 0;
	while (d->y < datas->nc.size_max_y - 1)
	{
		d->x = 2;
		while (d->x < datas->nc.size_max_x - 1 && i < MEM_SIZE)
		{
			ncurses_option_print(datas, d, i);
			ncurses_show_arene_element(datas, d, datas->arene[i]);
			d->x += 3;
			++i;
		}
		d->y++;
	}
	if (d->cur_champ != 0)
		wattroff(datas->nc.win, COLOR_PAIR(d->cur_champ));
}
