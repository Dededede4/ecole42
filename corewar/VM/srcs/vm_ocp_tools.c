/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_ocp_tools.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntoniolo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/08 15:18:36 by ntoniolo          #+#    #+#             */
/*   Updated: 2017/03/23 18:03:18 by gnebie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

int		vm_ocp_size(char ocp, int nb_arg, int op_flag)
{
	int i;

	i = 0;
	while (nb_arg)
	{
		ocp = ocp >> 2;
		if ((ocp & 3) == 1)
			i += 1;
		else if ((ocp & 3) == 2 && !op_flag)
			i += DIR_SIZE;
		else if ((ocp & 3) == 2 && op_flag)
			i += IND_SIZE;
		else if ((ocp & 3) == 3)
			i += IND_SIZE;
		nb_arg--;
	}
	return (i);
}

int		vm_havent_ocp(int op_code)
{
	if (op_code == OP_LIVE)
		return (DIR_SIZE);
	else if (op_code == OP_ZJMP || op_code == OP_FORK || op_code == OP_LFORK)
		return (IND_SIZE);
	return (0);
}

int		vm_have_ocp(int op_code)
{
	if (op_code != OP_LIVE && op_code != OP_FORK && op_code != OP_LFORK
		&& op_code != OP_ZJMP)
		return (1);
	return (0);
}
