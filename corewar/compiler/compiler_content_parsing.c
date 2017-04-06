/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   compiler_content.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mprevot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/21 19:10:32 by mprevot           #+#    #+#             */
/*   Updated: 2017/03/21 19:10:36 by mprevot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "compiler.h"

/*
** This function return the configuration for an humain-readable instruction.
**
** get_config("and");
** -> {"and", 3, {T_REG | T_DIR | T_IND, T_REG | T_IND | T_DIR, T_REG}, 6, 6,
**		"et (and  r1, r2, r3   r1&r2 -> r3", 1, 0}
**
** get_config("noexistlol");
** -> Error
*/

t_op		get_config(char *name)
{
	t_op	op;

	op = corewar_op_name2tab(name);
	if (op.name)
		return (op);
	if (*name)
		error("Unknow instruct\n");
	return (op);
}

/*
** This function return an int representing the end of an label.
**
** compiler_compile_get_label("l2:		sti r1, %:live, %1");
** -> 2
**
** compiler_compile_get_label("		and r1, %0, r1");
** -> -1
*/

int			compiler_compile_get_label(char *line)
{
	int		i;

	i = 0;
	while (line[i])
	{
		if (!ft_strchr(LABEL_CHARS, line[i]))
			break ;
		i++;
	}
	if (line[i] == LABEL_CHAR)
		return (i);
	return (-1);
}

/*
** This function return an int representing the type
** of the humain-readable argument.
**
** The second argument is the value of g_op_tab[6]
** (See get_config())
**
** get_argtype("r15", 0);
** -> T_REG
**
** get_argtype("-5", 0);
** -> T_IND
*/

int			get_argtype(char *str, int conf)
{
	int		type;

	type = T_UNK;
	if (*str == DIRECT_CHAR)
		type = T_DIR;
	if (*str == 'r')
		type = T_REG;
	if (*str == '-' || ft_isdigit(*str))
		type = T_IND;
	if (*str == DIRECT_CHAR && str[1] == LABEL_CHAR)
		type = T_LABDIR;
	if (str[0] == LABEL_CHAR)
		type = T_LABIND;
	if (type == T_UNK)
		error("Error : Unknow argtype.\n");
	if (type < T_LAB && (type & conf) == 0)
		error("Error : argtype\n");
	if (type == T_LABDIR && (T_DIR & conf) == 0)
		error("Error : argtype label\n");
	if (type == T_LABIND && (T_IND & conf) == 0)
		error("Error : argtype label\n");
	return (type);
}

/*
** This function return an new string representing the label name
** for an opcode argument.
**
** extract_str("%:loop")
** -> strdup("loop");
**
** extract_str("%loop")
** -> strdup("loop");
*/

char		*extract_str(char *str)
{
	int		end;
	int		start;

	end = 0;
	start = 0;
	while (str[start] && !ft_strchr(LABEL_CHARS, str[start]))
		start++;
	end = start;
	while (str[end] && ft_strchr(LABEL_CHARS, str[start]))
		end++;
	return (ft_strsub(str, start, end - start));
}

/*
** This function return the int asked by the opcode argument.
**
** extract_int("r16")
** -> 16
**
** extract_int("%-5")
** -> -5
*/

int			extract_int(char *str)
{
	int		start;

	start = 0;
	while (!(ft_isdigit(str[start]) || str[start] == '-'))
		start++;
	return (ft_atoi(str + start));
}
