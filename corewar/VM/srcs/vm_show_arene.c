/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_show_arene.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntoniolo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/21 22:05:56 by ntoniolo          #+#    #+#             */
/*   Updated: 2017/03/27 03:09:06 by ntoniolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

static void	vm_print_elem(t_datas *datas, char elem)
{
	char		line[3];

	(void)datas;
	line[2] = 0;
	line[1] = (unsigned char)elem % 16;
	line[0] = ((unsigned char)elem / 16) % 16;
	line[0] += (line[0] >= 10) ? ('a' - 10) : ('0');
	line[1] += (line[1] >= 10) ? ('a' - 10) : ('0');
	ft_printf("%s ", line);
}

int			vm_show_arene(t_datas *datas)
{
	int i;
	int	xmod;

	xmod = (datas->flag & FLAG_H) >= 1 ? 64 : 32;
	i = 0;
	ft_putstr("0x0000 : ");
	while (i < MEM_SIZE)
	{
		if (i % xmod == 0 && i)
			ft_printf("\n0x0%03x : ", i);
		vm_print_elem(datas, datas->arene[i]);
		i++;
	}
	ft_printf("\n");
	return (0);
}
