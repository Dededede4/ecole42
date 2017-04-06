/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_champ_process.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gnebie <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/12 14:03:12 by gnebie            #+#    #+#             */
/*   Updated: 2017/03/28 17:57:26 by ntoniolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

static void		vm_place_champ(t_datas *datas, char *arene,
												t_champ champ[MAX_PLAYERS + 1])
{
	int i;

	i = 0;
	while (i < datas->player_nbr)
	{
		ft_memset((void*)&datas->nc.background[(i) *
					(MEM_SIZE / datas->player_nbr)], i + 1,
					(size_t)champ[i].champ_size);
		ft_memcpy((void *)&arene[(i) *
					(MEM_SIZE / datas->player_nbr)], (void *)&champ[i],
					(size_t)champ[i].champ_size);
		datas->start[i] = i * (MEM_SIZE / datas->player_nbr);
		i++;
	}
}

void			vm_champ_process(t_datas *datas, int argc, char **argv)
{
	datas->player_nbr = vm_create_flags(datas, argv, argc, &datas->flag);
	datas->player_nbr = vm_init_champ(datas->begin_champ, argc, argv, datas);
	vm_verif_num_champ(datas);
	vm_place_champ(datas, datas->arene, datas->begin_champ);
}
