/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_do_cycles.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gnebie <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/12 05:20:51 by gnebie            #+#    #+#             */
/*   Updated: 2017/03/27 02:52:55 by ntoniolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

static void		vm_init_cycle(t_cycle *cycle)
{
	cycle->cycle = 0;
	cycle->total_cycle = 0;
	cycle->cycle_to_die = CYCLE_TO_DIE;
	cycle->check = 1;
}

static void		end_cycle(t_datas *datas, t_cycle *cycle)
{
	int i;

	cycle->total_cycle += cycle->cycle;
	vm_delete_unlive_process(datas);
	if (datas->lives->cycle_lives >= NBR_LIVE || cycle->check == MAX_CHECKS)
	{
		cycle->cycle_to_die -= CYCLE_DELTA;
		cycle->check = 1;
	}
	else
		cycle->check++;
	i = 0;
	while (i <= datas->player_nbr)
	{
		datas->inf[i].cycle_lives = 0;
		i++;
	}
	datas->lives->cycle_lives = 0;
}

static void		put_map_ncurses(t_datas *datas, t_cycle *cycle,
							void (**exec)(t_datas *, t_process *))
{
	ncurses_key(datas);
	ncurses_base(datas);
	if (datas->nc.key != NC_PAUSE)
	{
		if (datas->nc.wall_cycle - 1 == (cycle->total_cycle + cycle->cycle))
			datas->nc.key = NC_PAUSE;
		ncurses_light(datas);
		if (datas->nc.key == NC_SBS)
			datas->nc.key = NC_PAUSE;
		turn_process(datas, exec);
		cycle->cycle++;
	}
}

static int		run_cycle(t_datas *datas, t_cycle *cycle,
									void (**exec)(t_datas *, t_process *))
{
	cycle->cycle = 0;
	while (cycle->cycle_to_die <= 0 || cycle->cycle < cycle->cycle_to_die)
	{
		if (datas->flag & FLAG_M)
			put_map_ncurses(datas, cycle, exec);
		else
		{
			turn_process(datas, exec);
			cycle->cycle++;
		}
		if (datas->dump > 0 && cycle->cycle + cycle->total_cycle == datas->dump)
			return (vm_show_arene(datas));
		if (cycle->cycle_to_die <= 0)
			break ;
	}
	return (1);
}

int				vm_do_cycles(t_datas *datas,
									void (**exec)(t_datas *, t_process *))
{
	vm_init_cycle(&datas->cycle);
	while (datas->begin_process)
	{
		if (!(run_cycle(datas, &datas->cycle, exec)))
			return (0);
		end_cycle(datas, &datas->cycle);
	}
	datas->end = 1;
	return (0);
}
