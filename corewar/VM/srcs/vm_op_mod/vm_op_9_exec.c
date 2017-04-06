/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_op_9_exec.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gnebie <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/12 14:21:51 by gnebie            #+#    #+#             */
/*   Updated: 2017/03/17 17:29:03 by ntoniolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

/*
** zjmp
*/

void			vm_op_9_exec(t_datas *datas, t_process *process)
{
	if (process->carry)
		process->pc = vm_add_valid(process->pc +
			((vm_recup_arena_num(2, datas->arene, process->pc + 1) % IDX_MOD)));
	else
		process->pc = vm_add_valid(process->pc + 3);
}
