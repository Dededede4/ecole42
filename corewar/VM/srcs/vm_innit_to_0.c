/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_innit_to_0.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gnebie <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/12 05:12:17 by gnebie            #+#    #+#             */
/*   Updated: 2017/03/27 14:42:45 by ntoniolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

static void		innit_op_tab(t_datas *datas)
{
	t_op *op_tab_init;

	if (!(op_tab_init = corewar_op_tab()))
		exit(ft_int_error("echec de malloc de l'op_tab"));
	ft_memcpy((void*)&datas->op_tab[0], (void*)&op_tab_init[0], sizeof(t_op)
																		* 30);
	ft_memdel((void **)&op_tab_init);
}

static void		vm_innit_inf(t_datas *datas)
{
	int i;

	i = 0;
	while (i <= datas->player_nbr)
	{
		datas->inf[i].nbr_process = 0;
		datas->inf[i].total_lives = 0;
		datas->inf[i].cycle_lives = 0;
		datas->inf[i].cycle_last_live = 0;
		datas->inf[i].champion = i + 1;
		i++;
	}
}

void			vm_innit_to_0(t_datas *datas, t_champ *champs, t_lives *lives)
{
	ft_bzero((void *)datas, sizeof(t_datas));
	ft_bzero((void *)champs, sizeof(t_champ) * (MAX_PLAYERS + 1));
	ft_bzero((void *)lives, sizeof(t_lives));
	ft_bzero((void *)datas->arene, MEM_SIZE);
	ft_bzero((void *)datas->nc.background, MEM_SIZE);
	ft_bzero((void *)datas->nc.light, MEM_SIZE);
	datas->lives = lives;
	datas->begin_champ = champs;
	datas->nbr_cycles = CYCLE_TO_DIE;
	datas->nb_process = 0;
	datas->dump = -1;
	datas->end = 0;
	vm_innit_inf(datas);
	innit_op_tab(datas);
}
