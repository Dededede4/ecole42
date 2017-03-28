/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_create_process.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gnebie <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/12 05:14:18 by gnebie            #+#    #+#             */
/*   Updated: 2017/03/26 18:42:01 by ntoniolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

t_process	*vm_create_process(t_datas *datas, int nbr_champ)
{
	t_process	*process;
	t_process	*tmp;

	if (!(process = ft_memalloc(sizeof(t_process))))
		exit(vm_error(datas, "Malloc invalide"));
	tmp = datas->begin_process;
	datas->begin_process = process;
	process->next = tmp;
	process->pc = datas->start[nbr_champ - 1];
	process->champion = (char)nbr_champ;
	datas->inf[nbr_champ].nbr_process++;
	datas->inf[ALL].nbr_process++;
	process->carry = 0;
	process->nb = ++datas->nb_process;
	return (process);
}
