/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_start_op_code.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntoniolo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/16 13:31:48 by ntoniolo          #+#    #+#             */
/*   Updated: 2017/03/16 13:32:25 by ntoniolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void		start_op_code(t_datas *datas, t_process *pros, int op_code)
{
	pros->instruction = datas->op_tab[op_code].op_code;
	pros->cycle = datas->op_tab[op_code].cycle;
}
