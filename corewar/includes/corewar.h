/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   corewar.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gnebie <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/06 06:32:43 by gnebie            #+#    #+#             */
/*   Updated: 2017/03/27 13:56:33 by ntoniolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COREWAR_H
# define COREWAR_H

/*
** Includes
*/

# include "op.h"
# include "libft.h"
# include <ncurses.h>
# include <sys/time.h>
# include <signal.h>

/*
** Define
*/
# define NBR_FONC 25

# define OP_LIVE 1
# define OP_LD 2
# define OP_ST 3
# define OP_ADD 4
# define OP_SUB 5
# define OP_AND 6
# define OP_OR 7
# define OP_XOR 8
# define OP_ZJMP 9
# define OP_LDI 10
# define OP_STI 11
# define OP_FORK 12
# define OP_LLD 13
# define OP_LLDI 14
# define OP_LFORK 15
# define OP_AFF 16

# define INT_MAX 2147483647
# define INT_MIN -2147483648

/*
** Define flags
*/

# define FLAG_V 1
# define FLAG_B (1 << 1)
# define FLAG_N (1 << 2)
# define FLAG_M (1 << 3)
# define FLAG_K (1 << 4)
# define FLAG_G (1 << 5)
# define FLAG_H (1 << 6)
# define FLAG_D (1 << 7)
# define FLAG_DUMP (1 << 7)

/*
** Ncurses
*/

# define NC_PAUSE 'e'
# define NC_SBS 's'
# define NC_PROC_NEXT '+'
# define NC_PROC_BACK '-'
# define NC_PUT_NBR 'c'
# define NC_DEBUG_X datas->size_max_x + 2 + 3
# define NC_DEBUG_Y 23
# define NC_W_INF 70
# define ALL 0
# define NC_FIND_NBR 'f'
# define NC_COM_LEN (COMMENT_LENGTH + PROG_NAME_LENGTH + 12) * MAX_PLAYERS

/*
** MACROS
*/

# include "struct.h"
# include "prototypes.h"
#endif
