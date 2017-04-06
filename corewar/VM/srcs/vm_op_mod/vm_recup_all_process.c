/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_recup_all_process.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gnebie <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/12 14:50:32 by gnebie            #+#    #+#             */
/*   Updated: 2017/03/27 00:17:45 by ntoniolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

/*
** Flag :
** 0b1 : recupere le contenu du registre plutot que son numero
** 0b10 : prends un direct de 2 plutot qu'un direct de 4
** 0b100 : recupere le nombre indirect et non sa valeur
**	nombre = 2octet = definie adress;	valeur = 4octect a l'adress;
** 0b1000 :
** 0b10000 :
** 0b100000 :
** 0b1000000 :
** 0b10000000 :
*/

/*
**int			vm_recup_all_process(t_process *process, char *arene, int flg)
**{
**	int			tmp;
**	int			flag;
**	int			i;
**	int			adress;
**
**	i = -1;
**	adress = process->pc + 2;
**	while (++i < 4 && (tmp = (char)arene[vm_add_valid(process->pc + 1)] >> (2 *
**			(3 - i))) && (flag = flg >> (8 * (3 - i))) != -1)
**		if (((tmp & 3) == 0b01) && (adress += 1) && ((!(flag & 1) &&
**			(process->in_stock[i] = vm_recup_arena_num(1, arene, adress)) == -1)
**			|| ((vm_recup_process_reg(process, arene, adress,
**			&process->in_stock[i])) == -1)))
**				return (-1);
**		else if (((tmp & 3) == 0b10 && flag & 0b10 && (adress += 2)) ||
**		 		((tmp & 3) == 0b11 && flag & 0b100 && (adress += 2)))
**			process->in_stock[i] = vm_recup_arena_num(2, arene, adress - 2);
**		else if ((tmp & 3) == 0b10 && (adress += 4))
**			process->in_stock[i] = vm_recup_arena_num(4, arene, adress - 4);
**		else if ((tmp & 3) == 0b11 && (adress += 2))
**			process->in_stock[i] = vm_recup_indirect_num(process, arene, adress
** - 2);
**	return (0);
**}
*/

static int	vm_recup_all_process_dir(t_process *process, char *arene, int *inf,
																	int *adress)
{
	if (inf[1] & 0b10)
	{
		process->in_stock[inf[0]] = vm_recup_arena_num(2, arene, *adress);
		*adress += 2;
	}
	else
	{
		process->in_stock[inf[0]] = vm_recup_arena_num(4, arene, *adress);
		*adress += 4;
	}
	return (0);
}

static int	vm_recup_all_process_ind(t_process *process, char *arene, int *inf,
																	int *adress)
{
	if ((inf[2] & 3) == 0b11 && inf[1] & 0b100)
	{
		process->in_stock[inf[0]] = vm_recup_arena_num(2, arene, *adress);
		*adress += 2;
	}
	else
	{
		process->in_stock[inf[0]] = vm_recup_indirect_num(process, arene,
																	*adress);
		*adress += 2;
	}
	return (0);
}

static int	vm_recup_all_process_reg(t_process *process, char *arene,
													int *inf, int *adress)
{
	if (!(inf[1] & 1))
		process->in_stock[inf[0]] = vm_recup_arena_num(1, arene, *adress);
	else if ((vm_recup_process_reg(process, arene, *adress,
										&process->in_stock[inf[0]])) == -1)
		return (-1);
	*adress += 1;
	return (0);
}

int			vm_recup_all_process(t_process *process, char *arene, int flg)
{
	int			inf[3];
	int			adress;

	inf[0] = 0;
	adress = process->pc + 2;
	while (inf[0] < 4)
	{
		inf[1] = flg >> (8 * (3 - inf[0]));
		inf[2] = (char)arene[vm_add_valid(process->pc + 1)] >> (2 *
																(3 - inf[0]));
		if ((inf[2] & 3) == 0b01)
		{
			if (vm_recup_all_process_reg(process, arene, inf, &adress) == -1)
				return (-1);
		}
		else if ((inf[2] & 3) == 0b10)
			vm_recup_all_process_dir(process, arene, inf, &adress);
		else if ((inf[2] & 3) == 0b11)
			vm_recup_all_process_ind(process, arene, inf, &adress);
		inf[0]++;
	}
	return (0);
}
