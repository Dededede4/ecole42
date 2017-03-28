/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_op_15_exec.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gnebie <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/12 14:22:23 by gnebie            #+#    #+#             */
/*   Updated: 2017/03/25 23:18:36 by ntoniolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

/*
** L-fork
** 0f 03 70 03 ff ff 01
*/

void			vm_op_15_exec(t_datas *datas, t_process *process)
{
	vm_copy_process(datas, process, vm_add_valid(process->pc +
		(vm_recup_arena_num(2, datas->arene, process->pc + 1)) % MEM_SIZE));
	process->pc = vm_add_valid(process->pc + 3);
}
