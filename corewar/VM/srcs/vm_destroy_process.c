/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_destroy_process.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gnebie <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/12 05:13:18 by gnebie            #+#    #+#             */
/*   Updated: 2017/03/13 16:12:46 by ntoniolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void		vm_destroy_process(t_process *process, t_datas *datas)
{
	t_process	*process2;

	process2 = datas->begin_process;
	while (process2 && process2->next == process)
		process2 = process2->next;
	if (process2)
	{
		process2 = process->next;
		ft_memdel((void **)&process);
	}
}
