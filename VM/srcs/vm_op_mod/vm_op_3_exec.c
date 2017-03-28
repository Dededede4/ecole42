/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_op_3_exec.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gnebie <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/12 14:21:21 by gnebie            #+#    #+#             */
/*   Updated: 2017/03/27 00:34:10 by ntoniolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

/*
** St
** Prend un registre et un registre ou un indirect,
** et stocke la valeur du registre vers le second paramètre.
** Par exemple, st r1, 42 stocke la valeur de r1 à l’adresse
** (PC + (42 % IDX_MOD))
*/

void			vm_op_3_exec(t_datas *datas, t_process *process)
{
	char		i;

	i = datas->arene[vm_add_valid(process->pc + 1)];
	if (vm_verif_datas(datas, process))
	{
		if (!(vm_recup_all_process(process, datas->arene, 1 << 24 | 1 << 18)))
		{
			if (((i >> 4) & 3) == 1 && process->in_stock[1] > 0 &&
											process->in_stock[1] <= REG_NUMBER)
			{
				process->reg[process->in_stock[1]] = process->in_stock[0];
			}
			else if (((i >> 4) & 3) == 3)
			{
				vm_put_nbr_in_arene(process->in_stock[0], process->pc +
						(process->in_stock[1] % IDX_MOD), datas->arene, 4);
				ncurses_put_background(datas, process->pc +
						(process->in_stock[1] % IDX_MOD), process->champion, 4);
			}
		}
	}
	process->pc = vm_op_jump(datas, process,
							datas->op_tab[(int)process->instruction].nb_arg);
}
