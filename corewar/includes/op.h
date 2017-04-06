/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gnebie <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/06 06:33:08 by gnebie            #+#    #+#             */
/*   Updated: 2017/03/09 18:42:17 by ntoniolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** Mise a la norme
** Toutes les tailles sont en octets.
** On part du principe qu'un int fait 32 bits. Est-ce vrai chez vous ?
*/

#ifndef OP_H
# define OP_H

/*
** MACROS
*/

# define IND_SIZE				2
# define REG_SIZE				4
# define DIR_SIZE				REG_SIZE

# define REG_CODE				1
# define DIR_CODE				2
# define IND_CODE				3

# define MAX_ARGS_NUMBER		4
# define MAX_PLAYERS			4
# define MEM_SIZE				(4*1024)
# define IDX_MOD				(MEM_SIZE / 8)
# define CHAMP_MAX_SIZE			(MEM_SIZE / 6)

# define COMMENT_CHAR			'#'
# define LABEL_CHAR				':'
# define DIRECT_CHAR			'%'
# define SEPARATOR_CHAR			','

# define LABEL_CHARS			"abcdefghijklmnopqrstuvwxyz_0123456789"
# define OPCODE_CHARS			"abcdefghijklmnopqrstuvwxyz"

# define NAME_CMD_STRING		".name"
# define COMMENT_CMD_STRING		".comment"

# define REG_NUMBER				16

# define CYCLE_TO_DIE			1536
# define CYCLE_DELTA			50
# define NBR_LIVE				21
# define MAX_CHECKS				10

# define T_UNK					0
# define T_REG					1
# define T_DIR					2
# define T_IND					4
# define T_LAB					8
# define T_LABDIR				16
# define T_LABIND				32

# define PROG_NAME_LENGTH		(128)
# define COMMENT_LENGTH			(2048)
# define COREWAR_EXEC_MAGIC		0xea83f3

/*
** Typedefs
*/

typedef char	t_arg_type;

/*
** Structures
*/

typedef struct			s_header
{
	unsigned int		magic;
	char				prog_name[PROG_NAME_LENGTH + 1];
	unsigned int		prog_size;
	char				comment[COMMENT_LENGTH + 1];
}						t_header;

/*
** Prototypes
*/

#endif
