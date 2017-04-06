/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_op_2_exec.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gnebie <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/12 14:21:16 by gnebie            #+#    #+#             */
/*   Updated: 2017/03/27 00:42:56 by ntoniolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

/*
** ld recherche
** write the value of the first parameter in the second parameter(a register)2
** parameters T_DIR | T_IND, T_REG
** carry si carry = 1 passe le carry a 0
** si son op_code_instruc est erronne jump de 2
** lit le nombre de paramettres de l'octets d'encodage et jump de la taille de
** ses paramettes (exemple si 101010 et que deux paramettres jump de 1 + 2 * 4)
** ne check pas si les paramettes sont valides pour la fonction
** si repertory non valide ne fait rien / prends 0 a la place
** lit les insturctions a la fin de son cycle
**
** Si valeur de Load == 0 le CARRY == 1
** Sinon dans les autres cas, CARRY == 0
*/

void			vm_op_2_exec(t_datas *datas, t_process *process)
{
	if (vm_verif_datas(datas, process))
	{
		if (!(vm_recup_all_process(process, datas->arene, 1 << 24)))
		{
			if (process->in_stock[1] > 0 && process->in_stock[1] <= REG_NUMBER)
			{
				process->reg[process->in_stock[1]] = process->in_stock[0];
				if (0 == process->in_stock[0])
					process->carry = 1;
				else
					process->carry = 0;
			}
		}
	}
	process->pc = vm_op_jump(datas, process,
							datas->op_tab[(int)process->instruction].nb_arg);
}
