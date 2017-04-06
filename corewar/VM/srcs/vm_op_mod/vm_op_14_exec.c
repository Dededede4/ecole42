/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_op_14_exec.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gnebie <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/12 14:22:16 by gnebie            #+#    #+#             */
/*   Updated: 2017/03/26 23:47:05 by ntoniolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

/*
** Lldi
*/

void			vm_op_14_exec(t_datas *datas, t_process *process)
{
	if (vm_verif_datas(datas, process))
	{
		if (!(vm_recup_all_process(process, datas->arene,
										1 << 25 | 1 << 24 | 1 << 17 | 1 << 16)))
		{
			if (process->in_stock[2] > 0 && process->in_stock[2] <= REG_NUMBER)
			{
				process->reg[process->in_stock[2]] =
							vm_recup_arena_num(REG_SIZE, datas->arene,
								vm_add_valid(process->pc +
									vm_add_valid(process->in_stock[0] +
									process->in_stock[1])));
				if (process->reg[process->in_stock[2]] == 0)
					process->carry = 1;
				else
					process->carry = 0;
			}
		}
	}
	process->pc = vm_op_jump(datas, process,
							datas->op_tab[(int)process->instruction].nb_arg);
}
