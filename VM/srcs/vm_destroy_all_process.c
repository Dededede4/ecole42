/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_destroy_all_process.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntoniolo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/27 02:37:36 by ntoniolo          #+#    #+#             */
/*   Updated: 2017/03/27 02:37:56 by ntoniolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void			vm_destroy_all_process(t_datas *datas)
{
	t_process	*process;
	t_process	*tmp;

	process = datas->begin_process;
	while (process)
	{
		tmp = process;
		process = process->next;
		ft_memdel((void **)&tmp);
	}
}
