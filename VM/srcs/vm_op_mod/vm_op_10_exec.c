/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_op_10_exec.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gnebie <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/12 14:21:57 by gnebie            #+#    #+#             */
/*   Updated: 2017/03/27 00:38:35 by ntoniolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

/*
**Ldi
**{"ldi", 3, {T_REG | T_DIR | T_IND, T_DIR | T_REG, T_REG}, 10, 25,
**	"load index", 1, 1, 0},
*/

void			vm_op_10_exec(t_datas *datas, t_process *process)
{
	if (vm_verif_datas(datas, process))
	{
		if (!(vm_recup_all_process(process, datas->arene, 1 << 25 | 1 << 24 |
													1 << 16 | 1 << 17)))
		{
			if (process->in_stock[2] > 0 && process->in_stock[2] <= REG_NUMBER)
			{
				process->reg[process->in_stock[2]] = vm_recup_arena_num(4,
				datas->arene, vm_add_valid((process->pc + ((process->in_stock[0]
				+ process->in_stock[1]) % IDX_MOD))));
			}
		}
	}
	process->pc = vm_op_jump(datas, process,
							datas->op_tab[(int)process->instruction].nb_arg);
}
