/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_show_arene.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gnebie <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/07 09:42:01 by gnebie            #+#    #+#             */
/*   Updated: 2017/03/27 14:40:56 by ntoniolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

static void		init_draw(t_datas *datas, t_nc *nc, t_draw *d)
{
	int len;
	int i;

	d->max = 0;
	d->cur_champ = 0;
	d->count = 0;
	d->save_pros = 0;
	d->highlight = 0;
	d->y = 1;
	i = 0;
	len = 0;
	while (i < datas->player_nbr)
	{
		ft_strcpy(&nc->str_com[len], "  [");
		len = ft_strlen(nc->str_com);
		ft_strcpy(&nc->str_com[len], datas->begin_champ[i].champ_name);
		len = ft_strlen(nc->str_com);
		ft_strcpy(&nc->str_com[len], "] : ");
		len = ft_strlen(nc->str_com);
		ft_strcpy(&nc->str_com[len], datas->begin_champ[i].champ_com);
		len = ft_strlen(nc->str_com);
		i++;
	}
	nc->len_com = (int)ft_strlen(nc->str_com);
}

void			ncurses_base(t_datas *datas)
{
	t_draw	d;

	init_draw(datas, &datas->nc, &d);
	d.cur_champ = 255;
	datas->nc.i_print = 0;
	werase(datas->nc.win);
	werase(datas->nc.inf);
	box(datas->nc.win, 0, 0);
	box(datas->nc.inf, 0, 0);
	ncurses_find_pc(datas, &d);
	ncurses_loop_arene(datas, &d);
	print_cycle(datas, &datas->nc);
	print_kirby(datas, &datas->nc);
	print_main_menu(datas, &datas->nc);
	print_process(datas, &datas->nc);
	print_comment(datas, &datas->nc);
	wrefresh(datas->nc.win);
	wrefresh(datas->nc.inf);
}
