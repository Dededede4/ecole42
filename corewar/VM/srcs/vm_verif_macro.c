/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_verif_macro.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gnebie <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/09 02:20:12 by gnebie            #+#    #+#             */
/*   Updated: 2017/03/23 14:49:27 by gnebie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void		vm_verif_macro(void)
{
	if (IND_SIZE > 4 || REG_SIZE > 4 || DIR_SIZE > 4 ||
		IND_SIZE < 2 || REG_SIZE < 2 || DIR_SIZE < 2 ||
		REG_CODE != 1 || DIR_CODE != 2 || IND_CODE != 3 ||
		MAX_ARGS_NUMBER > 8 || MAX_PLAYERS > 8 ||
		MAX_ARGS_NUMBER < 2 || MAX_PLAYERS < 2 ||
		MEM_SIZE < (MAX_PLAYERS * CHAMP_MAX_SIZE) || MEM_SIZE < 0x100 ||
		MEM_SIZE > 0x10000 || CYCLE_TO_DIE < 0x100 || CYCLE_TO_DIE > 0x10000 ||
		CYCLE_DELTA < 10 || CYCLE_DELTA > (CYCLE_TO_DIE / 2) || NBR_LIVE < 1 ||
		NBR_LIVE > CYCLE_TO_DIE || MAX_CHECKS < 1 ||
		MAX_CHECKS > CYCLE_DELTA || T_REG != 1 || T_DIR != 2 || T_IND != 4 ||
		T_LAB != 8 || PROG_NAME_LENGTH < 16 || PROG_NAME_LENGTH > 0x1000 ||
		COMMENT_LENGTH < 0x80 || COMMENT_LENGTH > 0x1000 ||
		COREWAR_EXEC_MAGIC > 0x1000000)
		exit(ft_int_error("DEFINITON DES MACROS NON VALIDES"));
}
