/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ncurses_cycle.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntoniolo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/17 18:42:25 by ntoniolo          #+#    #+#             */
/*   Updated: 2017/03/20 18:09:22 by ntoniolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void		print_cycle(t_datas *datas, t_nc *nc)
{
	wattron(nc->inf, WA_UNDERLINE);
	mvwprintw(nc->inf, ++nc->i_print, 2, "Total Cycles",
										WA_UNDERLINE | WA_LOW);
	wattroff(nc->inf, WA_UNDERLINE);
	mvwprintw(nc->inf, nc->i_print, 20, "Current Cycles / ");
	mvwprintw(nc->inf, nc->i_print, 37, "Cycles to die");
	mvwprintw(nc->inf, ++nc->i_print, 2, "[%7lld   ]",
							datas->cycle.total_cycle + datas->cycle.cycle);
	mvwprintw(nc->inf, nc->i_print, 28, "[%-4lld] /", datas->cycle.cycle);
	mvwprintw(nc->inf, nc->i_print, 37, "[%-4lld]", datas->cycle.cycle_to_die);
	nc->i_print += 2;
	mvwhline(nc->inf, nc->i_print, 1, 0, 68);
}
