/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_champ_position_to_number.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gnebie <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/12 14:49:02 by gnebie            #+#    #+#             */
/*   Updated: 2017/03/12 14:49:03 by gnebie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

int				vm_champ_position_to_number(int champ_pos, t_champ *champ_tab)
{
	if ((unsigned int)champ_pos < CHAMP_MAX_SIZE)
		return (champ_tab[champ_pos].champ_nbr);
	return (0);
}
