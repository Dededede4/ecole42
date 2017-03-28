/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ncurses_process.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntoniolo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/19 23:03:13 by ntoniolo          #+#    #+#             */
/*   Updated: 2017/03/27 14:29:11 by ntoniolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

static void			print_inf(t_datas *datas, t_nc *nc, t_process *pros)
{
	wattroff(datas->nc.inf, COLOR_PAIR(pros->champion)
									| WA_UNDERLINE | WA_BOLD);
	mvwaddch(nc->win, pros->pc / 64 + 1, pros->pc % 64 * 3 + 2, 'L');
	mvwaddch(nc->win, pros->pc / 64 + 1, pros->pc % 64 * 3 + 3, 'A');
	mvwprintw(nc->inf, ++nc->i_print, 3, "Nb[%li]", pros->nb);
	mvwprintw(nc->inf, ++nc->i_print, 3,
			"Reg : [%x][%x][%x][%x][%x][%x][%x][%x]",
			pros->reg[1], pros->reg[2], pros->reg[3], pros->reg[4],
			pros->reg[5], pros->reg[6], pros->reg[7], pros->reg[8]);
	mvwprintw(nc->inf, ++nc->i_print, 3,
			"Reg : [%x][%x][%x][%x][%x][%x][%x][%x]",
			pros->reg[9], pros->reg[10], pros->reg[11], pros->reg[12],
			pros->reg[13], pros->reg[14], pros->reg[15], pros->reg[16]);
	nc->i_print++;
	mvwprintw(nc->inf, ++nc->i_print, 3, "PC    [%i]", pros->pc);
	mvwprintw(nc->inf, ++nc->i_print, 3, "Cycle [%i]", pros->cycle);
	mvwprintw(nc->inf, ++nc->i_print, 3, "OpCod [%i]", pros->instruction);
	mvwprintw(nc->inf, ++nc->i_print, 3, "Carry [%i]", pros->carry);
	mvwprintw(nc->inf, ++nc->i_print, 3, "Live  [%i]", pros->live);
	nc->i_print++;
	mvwprintw(nc->inf, ++nc->i_print, 3, "In_stock  [%x][%x][%x]",
				pros->in_stock[0], pros->in_stock[1], pros->in_stock[2]);
}

static t_process	*find_process(t_datas *datas, t_nc *nc, int *nbr_process)
{
	t_process	*pros;
	t_process	*tmp;
	int			i;

	pros = NULL;
	*nbr_process = datas->inf[nc->cur_menu].nbr_process;
	i = datas->inf[nc->cur_menu].nbr_process;
	tmp = datas->begin_process;
	while (tmp && i != datas->inf[nc->cur_menu].cur_process)
	{
		if ((tmp->champion == nc->cur_menu) || nc->cur_menu == 0)
		{
			i--;
			pros = tmp;
		}
		tmp = tmp->next;
	}
	nc->i_print += 6;
	mvwhline(nc->inf, nc->i_print - 2, 1, 0, 68);
	mvwprintw(nc->inf, nc->i_print, 9, "Process %i/%i",
			datas->inf[nc->cur_menu].cur_process + 1, *nbr_process);
	return (pros);
}

void				print_process(t_datas *datas, t_nc *nc)
{
	t_process	*pros;
	int			nbr_process;

	pros = find_process(datas, nc, &nbr_process);
	if (pros)
	{
		wattron(datas->nc.inf, COLOR_PAIR(pros->champion)
				| WA_UNDERLINE | WA_BOLD);
		mvwprintw(nc->inf, nc->i_print, 9, "Process %i/%i",
				datas->inf[nc->cur_menu].cur_process + 1, nbr_process);
		print_inf(datas, nc, pros);
	}
}
