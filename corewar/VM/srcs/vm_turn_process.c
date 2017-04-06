/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_turn_process.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntoniolo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/27 02:34:28 by ntoniolo          #+#    #+#             */
/*   Updated: 2017/03/28 00:04:55 by ntoniolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

static void		init_cycle_process(t_datas *datas, t_process *pros)
{
	unsigned int	cur_ocp;
	unsigned int	nbr_fonc;

	pros->in_stock[0] = 0;
	pros->in_stock[1] = 0;
	pros->in_stock[2] = 0;
	pros->in_stock[3] = 0;
	cur_ocp = (unsigned int)datas->arene[pros->pc];
	nbr_fonc = (datas->flag & FLAG_B) ? 25 : 17;
	if (nbr_fonc <= cur_ocp)
		cur_ocp = 0;
	start_op_code(datas, pros, cur_ocp);
}

int				turn_process(t_datas *datas,
								void (**exec)(t_datas *, t_process *))
{
	t_process		*pros;

	pros = datas->begin_process;
	while (pros)
	{
		if (pros->cycle == 0)
			init_cycle_process(datas, pros);
		if (pros->cycle == 1)
			exec[(int)pros->instruction](datas, pros);
		pros->cycle--;
		if (pros->cycle < 0)
			ft_printf("erreur procycle");
		pros = pros->next;
	}
	return (0);
}
