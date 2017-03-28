/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_op_8_exec.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gnebie <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/12 14:21:46 by gnebie            #+#    #+#             */
/*   Updated: 2017/03/27 00:36:31 by ntoniolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

/*
**Xor
*/

void			vm_op_8_exec(t_datas *datas, t_process *process)
{
	if (vm_verif_datas(datas, process))
	{
		if (!(vm_recup_all_process(process, datas->arene, 1 << 24 | 1 << 16)))
		{
			if (process->in_stock[2] > 0 && process->in_stock[2] <= REG_NUMBER)
			{
				process->reg[process->in_stock[2]] = process->in_stock[0]
														^ process->in_stock[1];
				if ((process->in_stock[0] ^ process->in_stock[1]) == 0)
					process->carry = 1;
				else
					process->carry = 0;
			}
		}
	}
	process->pc = vm_op_jump(datas, process,
							datas->op_tab[(int)process->instruction].nb_arg);
}
