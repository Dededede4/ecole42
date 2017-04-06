/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_op_jump.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gnebie <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/14 16:11:19 by gnebie            #+#    #+#             */
/*   Updated: 2017/03/26 00:11:24 by ntoniolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

int			vm_op_jump(t_datas *datas, t_process *process, unsigned char size)
{
	unsigned char		i;
	unsigned int		instruc;
	int					pr_i;

	i = 4 - size;
	instruc = process->instruc;
	pr_i = process->instruction;
	while (i)
	{
		instruc >>= 2;
		--i;
	}
	while (instruc)
	{
		((instruc & 3) == 1) ? i += 1 : 0;
		((instruc & 3) == 2 && !datas->op_tab[pr_i].nbr_octet_dir) ? i += 4 : 0;
		((instruc & 3) == 2 && datas->op_tab[pr_i].nbr_octet_dir) ? i += 2 : 0;
		((instruc & 3) == 3) ? i += 2 : 0;
		instruc >>= 2;
	}
	return (vm_add_valid(process->pc + 2 + i));
}
