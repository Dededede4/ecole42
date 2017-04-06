/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_op_12_exec.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gnebie <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/12 14:22:07 by gnebie            #+#    #+#             */
/*   Updated: 2017/03/24 17:17:39 by ntoniolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

/*
** Fork
*/

void			vm_op_12_exec(t_datas *datas, t_process *process)
{
	vm_copy_process(datas, process, vm_add_valid(process->pc +
		vm_recup_arena_num(2, datas->arene, process->pc + 1) % IDX_MOD));
	process->pc = vm_add_valid(process->pc + 3);
}
