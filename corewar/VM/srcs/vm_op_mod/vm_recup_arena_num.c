/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_recup_arena_num.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gnebie <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/12 14:49:28 by gnebie            #+#    #+#             */
/*   Updated: 2017/03/24 22:09:03 by ntoniolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

int			vm_recup_arena_num(int size, char *arene, int pc)
{
	int		i;
	int		res;

	i = 0;
	res = 0;
	while (i < size)
	{
		res <<= 8;
		res |= (unsigned char)arene[(pc + i) % MEM_SIZE];
		i++;
	}
	if (size == 1 && (res >> 7) == 1)
		res |= 0xffffff00;
	if (size == 2 && (res >> 15) == 1)
		res |= 0xffff0000;
	if (size == 3 && (res >> 23) == 1)
		res |= 0xff000000;
	return (res);
}
