/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_put_nbr_in_arene.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gnebie <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/14 18:51:47 by gnebie            #+#    #+#             */
/*   Updated: 2017/03/14 18:51:49 by gnebie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void			vm_put_nbr_in_arene(int number, int adress, char *arene,
																	int size)
{
	(adress < 0) ? (adress += MEM_SIZE) : 0;
	while (size)
	{
		arene[adress % MEM_SIZE] = (char)((number >> (8 * 3)));
		++adress;
		number <<= 8;
		--size;
	}
}
