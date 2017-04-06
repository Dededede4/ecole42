/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_copy_process.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gnebie <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/12 05:15:52 by gnebie            #+#    #+#             */
/*   Updated: 2017/03/24 16:40:08 by ntoniolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

t_process		*vm_copy_process(t_datas *datas, t_process *process, int pc)
{
	t_process		*new;
	t_process		*tmp;

	new = vm_create_process(datas, process->champion);
	tmp = new->next;
	ft_memmove((void *)new, (void *)process, sizeof(process->reg));
	new->next = tmp;
	new->pc = pc;
	new->live = process->live;
	new->carry = process->carry;
	new->champion = process->champion;
	return (new);
}
