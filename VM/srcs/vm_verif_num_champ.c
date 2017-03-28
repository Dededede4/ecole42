/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_verif_num_champ.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntoniolo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/28 17:35:19 by ntoniolo          #+#    #+#             */
/*   Updated: 2017/03/28 17:52:21 by ntoniolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void		vm_verif_num_champ(t_datas *datas)
{
	int i;
	int j;

	i = 0;
	while (i < datas->player_nbr)
	{
		j = i + 1;
		while (j < datas->player_nbr)
		{
			if (datas->begin_champ[i].champ_nbr ==
					datas->begin_champ[j].champ_nbr)
			{
				ft_printf("Don't duplicate number ! (Champ are native 1:");
				exit(ft_int_error(" -1 2: -2 3: -3 4: -4"));
			}
			j++;
		}
		i++;
	}
}
