/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_op_1_exec.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gnebie <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/12 14:21:10 by gnebie            #+#    #+#             */
/*   Updated: 2017/03/27 02:09:28 by ntoniolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

/*
** live recherche
** prends un paramettre, sur 4 octets
** lit live sur ce paramettre et inscrit live
** si 0 live durant le jeu le vainqueur est le dernier champion a arriver
** un processeur qui fait un live non valide reste en vie
** les lives non valides ne sont pas ajouter au decompte des lives totaux
** le prcesseur jump ensuite sur pc + 5
*/

void				vm_incr_lives(t_datas *datas, int arg1, int arg2)
{
	if (datas->flag & FLAG_M)
	{
		datas->inf[arg2 + 1].total_lives++;
		datas->inf[arg2 + 1].cycle_lives++;
		datas->inf[arg2 + 1].cycle_last_live = datas->cycle.cycle +
											datas->cycle.total_cycle + 1;
		datas->inf[ALL].total_lives++;
		datas->inf[ALL].cycle_lives++;
		datas->inf[ALL].cycle_last_live = datas->cycle.cycle +
											datas->cycle.total_cycle + 1;
	}
	datas->lives->total_lives++;
	datas->lives->champ_total_lives[arg2]++;
	datas->lives->champ_cycle_lives[arg2]++;
	datas->lives->last_live = arg1;
	datas->lives->cycle_last_live = datas->cycle.cycle
								+ datas->cycle.total_cycle + 1;
}

void				vm_op_1_exec(t_datas *datas, t_process *process)
{
	int		arg1;
	int		arg2;

	arg1 = vm_recup_arena_num(4, datas->arene, process->pc + 1);
	arg2 = vm_champ_number_to_position(arg1, datas->begin_champ);
	process->live = 1;
	process->pc = vm_add_valid(process->pc + 5);
	if (arg2 != -1)
	{
		vm_incr_lives(datas, arg1, arg2);
		if (datas->flag & FLAG_V)
			ft_printf("Player %i (%s) is said to be alive\n",
					datas->begin_champ[(int)process->champion - 1].champ_nbr,
					datas->begin_champ[(int)process->champion - 1].champ_name);
	}
	datas->lives->cycle_lives++;
}
