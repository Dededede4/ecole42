/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_ncurses.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntoniolo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/11 16:23:46 by ntoniolo          #+#    #+#             */
/*   Updated: 2017/03/28 13:07:37 by ntoniolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

static void	struct_init(t_nc *nc)
{
	nc->key = NC_PAUSE;
	nc->cur_pros = 0;
	nc->wall_cycle = -5;
	nc->i_com = 50;
	nc->sort_cycle = -1;
	gettimeofday(&nc->t1, NULL);
	gettimeofday(&nc->t2, NULL);
}

void		ncurses_init(t_datas *datas, int height, int width)
{
	struct_init(&datas->nc);
	initscr();
	cbreak();
	keypad(stdscr, TRUE);
	start_color();
	init_pair(1, COLOR_RED, COLOR_BLACK);
	init_pair(2, COLOR_BLUE, COLOR_BLACK);
	init_pair(3, COLOR_GREEN, COLOR_BLACK);
	init_pair(4, COLOR_MAGENTA, COLOR_BLACK);
	init_pair(5, COLOR_CYAN, COLOR_BLACK);
	datas->nc.cur_menu = 0;
	datas->nc.win = newwin(height, width, 0, 0);
	datas->nc.inf = newwin(height, NC_W_INF, 0, datas->nc.size_max_x + 2);
	cbreak();
}
