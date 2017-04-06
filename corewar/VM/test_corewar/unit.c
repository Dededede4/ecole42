/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntoniolo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/27 20:43:27 by ntoniolo          #+#    #+#             */
/*   Updated: 2017/03/28 00:43:17 by ntoniolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "script.h"

int			run_test_unit(t_env *e)
{
	ft_bzero(e->cmd, 500);
	sprintf(e->cmd, "./%s -h %i %s  > %s", "corewar", e->dump, e->str_unit,
															"ret_corewar.txt");
	system(e->cmd);
	ft_bzero(e->cmd, 500);
	sprintf(e->cmd, "./%s -d %i %s > %s", "corewar_zaz", e->dump, e->str_unit,
														"ret_corewar_zaz.txt");
	system(e->cmd);
	ft_bzero(e->cmd, 500);
	sprintf(e->cmd, "diff -rcs %s %s", "ret_corewar.txt",
												"ret_corewar_zaz.txt");
	system(e->cmd);
	ft_printf("Fin de [%s%i %s]\n", "./corewar -d ", e->dump, e->str_unit);
	e->i_champ++;
	return (0);
}
