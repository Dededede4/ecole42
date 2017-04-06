/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   corewar_op_tab.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gnebie <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/23 17:15:18 by gnebie            #+#    #+#             */
/*   Updated: 2017/03/23 17:35:35 by gnebie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

/*
**instructions suplementaires
** MUL = multiplier
** DIV = diviser (division par 0 == 0)
** NOT = d'un int
** ASL = (decalage d'un bit a gauche)
** ASR = (decalage d'un bit a droite)
** ROL = (rotation des bits d'un tout vers la gauche)
** ROR = (rotation des bits d'un tout vers la droite)
** MOV = copie un registe dans un autre
*/

static t_op g_op_tab[40] =
{
	{0, 0, {0}, 0, 1, 0, 0, 0},
	{"live", 1, {T_DIR}, 1, 10, "alive", 0, 0},
	{"ld", 2, {T_DIR | T_IND, T_REG}, 2, 5, "load", 1, 0},
	{"st", 2, {T_REG, T_IND | T_REG}, 3, 5, "store", 1, 0},
	{"add", 3, {T_REG, T_REG, T_REG}, 4, 10, "addition", 1, 0},
	{"sub", 3, {T_REG, T_REG, T_REG}, 5, 10, "soustraction", 1, 0},
	{"and", 3, {T_REG | T_DIR | T_IND, T_REG | T_IND | T_DIR, T_REG}, 6, 6,
		"et (and  r1, r2, r3   r1&r2 -> r3", 1, 0},
	{"or", 3, {T_REG | T_IND | T_DIR, T_REG | T_IND | T_DIR, T_REG}, 7, 6,
		"ou  (or   r1, r2, r3   r1 | r2 -> r3", 1, 0},
	{"xor", 3, {T_REG | T_IND | T_DIR, T_REG | T_IND | T_DIR, T_REG}, 8, 6,
		"ou (xor  r1, r2, r3   r1^r2 -> r3", 1, 0},
	{"zjmp", 1, {T_DIR}, 9, 20, "jump if zero", 0, 1},
	{"ldi", 3, {T_REG | T_DIR | T_IND, T_DIR | T_REG, T_REG}, 10, 25,
		"load index", 1, 1},
	{"sti", 3, {T_REG, T_REG | T_DIR | T_IND, T_DIR | T_REG}, 11, 25,
		"store index", 1, 1},
	{"fork", 1, {T_DIR}, 12, 800, "fork", 0, 1},
	{"lld", 2, {T_DIR | T_IND, T_REG}, 13, 10, "long load", 1, 0},
	{"lldi", 3, {T_REG | T_DIR | T_IND, T_DIR | T_REG, T_REG}, 14, 50,
		"long load index", 1, 1},
	{"lfork", 1, {T_DIR}, 15, 1000, "long fork", 0, 1},
	{"aff", 1, {T_REG}, 16, 2, "aff", 1, 0},
	{"mul", 3, {T_REG | T_DIR | T_IND, T_REG | T_IND | T_DIR, T_REG}, 17, 36,
		"multiplier (mul  r1, r2, r3   r1*r2 -> r3", 1, 0},
	{"div", 3, {T_REG | T_DIR | T_IND, T_REG | T_IND | T_DIR, T_REG}, 18, 36,
		"diviser (div  r1, r2, r3   r1/r2 -> r3", 1, 0},
	{"not", 2, {T_REG | T_IND | T_DIR, T_REG}, 19, 6,
		"non binaire (not  r1, r2   r1~ -> r2", 1, 0},
	{"asl", 2, {T_REG | T_IND | T_DIR, T_REG}, 20, 12,
		"decalage binaire a gauche (asl r1, r2   r1<<1 -> r2", 1, 0},
	{"asr", 2, {T_REG | T_IND | T_DIR, T_REG}, 21, 12,
		"decalage binaire a droite (asr r1, r2   r1>>1 -> r2", 1, 0},
	{"rol", 2, {T_REG | T_IND | T_DIR, T_REG}, 22, 12,
		"rotation binaire a gauche (rol r1, r2   r1<<1 -> r2", 1, 0},
	{"ror", 2, {T_REG | T_IND | T_DIR, T_REG}, 23, 12,
		"rotation binaire a droite (ror r1, r2   r1>>1 -> r2", 1, 0},
	{"mov", 2, {T_REG, T_REG}, 24, 4,
		"copier un registre dans un autre (mov  r1, r2  r1->r2", 1, 0},
	{0, 0, {0}, 0, 0, 0, 0, 0}
};

t_op		*corewar_op_tab(void)
{
	t_op *op_tab;

	if (!(op_tab = ft_memalloc(sizeof(t_op) * 40)))
	{
		write(2, "echec de malloc op_tab\n", 23);
		exit(-1);
	}
	ft_memcpy((void*)&op_tab[0], (void*)&g_op_tab[0], sizeof(t_op) * 40);
	return (op_tab);
}

/*
** This function return the configuration for an humain-readable instruction.
**
** get_config("and");
** -> {"and", 3, {T_REG | T_DIR | T_IND, T_REG | T_IND | T_DIR, T_REG}, 6, 6,
**		"et (and  r1, r2, r3   r1&r2 -> r3", 1, 0}
**
** get_config("noexistlol");
** -> {0, 0, {0}, 0, 0, 0, 0, 0}
*/

t_op		corewar_op_name2tab(char *name)
{
	int		i;

	i = 1;
	while (g_op_tab[i].name)
	{
		if (ft_strcmp((char*)g_op_tab[i].name, name) == 0)
			return (g_op_tab[i]);
		i++;
	}
	return (g_op_tab[i]);
}
