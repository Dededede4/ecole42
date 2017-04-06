/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_op_4_exec.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gnebie <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/12 14:21:26 by gnebie            #+#    #+#             */
/*   Updated: 2017/03/27 00:34:32 by ntoniolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

/*
** Add
** Prend trois registres,
** additionne les 2 premiers,
** met le résultat dans le troisième,
** juste avant de modifier le carry.
*/

void			vm_op_4_exec(t_datas *datas, t_process *process)
{
	if (vm_verif_datas(datas, process))
	{
		if (!(vm_recup_all_process(process, datas->arene, 1 << 24 | 1 << 16)))
		{
			if (process->in_stock[2] > 0 && process->in_stock[2] <= REG_NUMBER)
			{
				process->reg[process->in_stock[2]] = process->in_stock[0] +
														process->in_stock[1];
				if (process->in_stock[0] + process->in_stock[1] == 0)
					process->carry = 1;
				else
					process->carry = 0;
			}
		}
	}
	process->pc = vm_op_jump(datas, process,
							datas->op_tab[(int)process->instruction].nb_arg);
}
