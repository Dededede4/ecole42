/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_op_11_exec.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gnebie <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/12 14:22:02 by gnebie            #+#    #+#             */
/*   Updated: 2017/03/26 20:07:00 by ntoniolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

/*
** sti
** si le repertoire n'existe pas, ne rien faire
** n'ecrit pas
*/

void			vm_op_11_exec(t_datas *datas, t_process *process)
{
	char		i;

	i = datas->arene[vm_add_valid(process->pc + 1)];
	if (vm_verif_datas(datas, process))
	{
		if (!vm_recup_all_process(process, datas->arene, 1 << 24 | 1 << 17 |
												1 << 16 | 1 << 9 | 1 << 8))
		{
			vm_put_nbr_in_arene(process->in_stock[0], vm_add_valid(process->pc +
				((process->in_stock[1] + process->in_stock[2]) % IDX_MOD)),
				datas->arene, 4);
			ncurses_put_background(datas, vm_add_valid(process->pc +
				((process->in_stock[1] + process->in_stock[2]) % IDX_MOD)),
				process->champion, 4);
		}
	}
	process->pc = vm_op_jump(datas, process,
							datas->op_tab[(int)process->instruction].nb_arg);
}
