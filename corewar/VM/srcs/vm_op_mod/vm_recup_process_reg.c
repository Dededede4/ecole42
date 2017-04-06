/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_recup_process_reg.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gnebie <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/12 14:50:15 by gnebie            #+#    #+#             */
/*   Updated: 2017/03/14 12:50:46 by ntoniolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

int				vm_recup_process_reg(t_process *process, char *arene,
													int adresse, int *result)
{
	unsigned int		reg;

	reg = vm_recup_arena_num(1, arene, adresse);
	if (reg && reg <= REG_NUMBER)
	{
		*result = process->reg[reg];
		*result = *result >> (4 * 8 - REG_SIZE * 8);
	}
	else
		return (-1);
	return (0);
}
