/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_op_23_exec.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gnebie <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/24 18:35:18 by gnebie            #+#    #+#             */
/*   Updated: 2017/03/27 00:47:38 by ntoniolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

/*
** rotation droite
*/

void			vm_op_23_exec(t_datas *datas, t_process *process)
{
	if (vm_verif_datas(datas, process))
	{
		if (!(vm_recup_all_process(process, datas->arene, 1 << 24)))
		{
			if (process->in_stock[1] > 0 && process->in_stock[1] <= REG_NUMBER)
			{
				process->reg[process->in_stock[1]] = process->in_stock[0] >> 1 |
											(process->in_stock[0] & 1) << 31;
				if (!process->reg[process->in_stock[1]])
					process->carry = 1;
				else
					process->carry = 0;
			}
		}
	}
	process->pc = vm_op_jump(datas, process,
							datas->op_tab[(int)process->instruction].nb_arg);
}
