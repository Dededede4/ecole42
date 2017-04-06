/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_print.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntoniolo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/27 00:58:25 by ntoniolo          #+#    #+#             */
/*   Updated: 2017/03/27 01:16:06 by ntoniolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void		vm_print_start_battle(t_datas *datas)
{
	int i;

	i = 0;
	ft_printf("Introducing contestants...\n");
	while (i < datas->player_nbr)
	{
		ft_printf("* Player %i, weighing %i bytes, \"%s\" (\"%s\") !\n",
			i + 1, datas->begin_champ[i].champ_size,
			datas->begin_champ[i].champ_name, datas->begin_champ[i].champ_com);
		i++;
	}
}
