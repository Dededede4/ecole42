/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_print_end_battle.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntoniolo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/27 01:15:41 by ntoniolo          #+#    #+#             */
/*   Updated: 2017/03/27 02:53:22 by ntoniolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void		vm_print_end_battle(t_datas *datas)
{
	int ret;

	ret = datas->lives->last_live;
	if (ret)
	{
		ft_printf("Contestant %i, \"%s\", has won !\n",
			vm_champ_number_to_position(ret, datas->begin_champ) + 1,
			datas->begin_champ[vm_champ_number_to_position(ret,
				datas->begin_champ)].champ_name);
	}
	else
	{
		ft_printf("Contestant %i, \"%s\", has won !\n",
		datas->player_nbr,
		datas->begin_champ[datas->player_nbr - 1].champ_name);
	}
}
