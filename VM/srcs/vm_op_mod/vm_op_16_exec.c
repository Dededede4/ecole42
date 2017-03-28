/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_op_16_exec.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gnebie <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/12 14:22:29 by gnebie            #+#    #+#             */
/*   Updated: 2017/03/28 20:35:35 by ntoniolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void			vm_op_16_exec(t_datas *datas, t_process *process)
{
	int	i;

	i = 0;
	if ((vm_verif_datas(datas, process)))
	{
		if (!(datas->flag & FLAG_H) && !(datas->flag & FLAG_DUMP) &&
			!(datas->flag & FLAG_M) && (vm_recup_process_reg(process,
					datas->arene, process->pc + 2, &i)) != -1)
			ft_printf("aff [%2c](value %0#.2hhx)\n", i % 256, i);
	}
	process->pc = vm_op_jump(datas, process,
		datas->op_tab[(int)process->instruction].nb_arg);
}
