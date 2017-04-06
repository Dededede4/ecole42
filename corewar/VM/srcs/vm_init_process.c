/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_init_process.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gnebie <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/12 05:30:04 by gnebie            #+#    #+#             */
/*   Updated: 2017/03/26 18:01:47 by ntoniolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

static int			vm_op_create_exec_2(t_datas *datas, void (*exec[NBR_FONC])
										(t_datas *, t_process *))
{
	exec[17] = vm_op_17_exec;
	exec[18] = vm_op_18_exec;
	exec[19] = vm_op_19_exec;
	exec[20] = vm_op_20_exec;
	exec[21] = vm_op_21_exec;
	exec[22] = vm_op_22_exec;
	exec[23] = vm_op_23_exec;
	exec[24] = vm_op_24_exec;
	return (vm_do_cycles(datas, exec));
}

static int			vm_op_create_exec(t_datas *datas)
{
	void		(*exec[NBR_FONC])(t_datas *, t_process *);

	if (NBR_FONC != 25)
		exit(ft_int_error("Mauvais nombre de fonctions"));
	exec[0] = vm_op_0_exec;
	exec[1] = vm_op_1_exec;
	exec[2] = vm_op_2_exec;
	exec[3] = vm_op_3_exec;
	exec[4] = vm_op_4_exec;
	exec[5] = vm_op_5_exec;
	exec[6] = vm_op_6_exec;
	exec[7] = vm_op_7_exec;
	exec[8] = vm_op_8_exec;
	exec[9] = vm_op_9_exec;
	exec[10] = vm_op_10_exec;
	exec[11] = vm_op_11_exec;
	exec[12] = vm_op_12_exec;
	exec[13] = vm_op_13_exec;
	exec[14] = vm_op_14_exec;
	exec[15] = vm_op_15_exec;
	exec[16] = vm_op_16_exec;
	return (vm_op_create_exec_2(datas, exec));
}

int					vm_init_process(t_datas *datas)
{
	t_process		*process;
	int				i;

	i = 0;
	while (i < datas->player_nbr)
	{
		process = vm_create_process(datas, i + 1);
		process->reg[1] = datas->begin_champ[i].champ_nbr;
		process->carry = 0;
		i++;
	}
	vm_op_create_exec(datas);
	return (0);
}
