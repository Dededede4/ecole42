/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntoniolo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/30 17:58:40 by ntoniolo          #+#    #+#             */
/*   Updated: 2017/03/28 00:41:52 by ntoniolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "script.h"

static void		do_test(t_env *e)
{
	ft_bzero(e->cmd, 500);
	sprintf(e->cmd, "./%s -h %i %s %s %s %s > %s", "corewar", e->dump,
		g_player[e->i_champ], g_player[e->j], g_player[e->y], g_player[e->b],
													"ret_corewar.txt");
	system(e->cmd);
	ft_bzero(e->cmd, 500);
	sprintf(e->cmd, "./%s -d %i %s %s %s %s > %s", "corewar_zaz", e->dump,
		g_player[e->i_champ], g_player[e->j], g_player[e->y], g_player[e->b],
													"ret_corewar_zaz.txt");
	system(e->cmd);
	ft_printf("{%i}|Fin de [%s] ||| i_champ[%i] | j[%i] | y[%i] | b[%i]\n",
							e->count, e->cmd, e->i_champ, e->j, e->y, e->b);
	ft_bzero(e->cmd, 500);
	sprintf(e->cmd, "diff -rcs %s %s", "ret_corewar.txt",
													"ret_corewar_zaz.txt");
	system(e->cmd);
}

static void		turn_over(t_env *e)
{
	while (e->count < e->nb_test)
	{
		e->i_champ = rd(&e->rd) % e->nb_player;
		e->j = rd(&e->rd) % e->nb_player;
		e->y = rd(&e->rd) % e->nb_player;
		e->b = rd(&e->rd) % e->nb_player;
		do_test(e);
		e->count++;
	}
}

int				run_test_rd(t_env *e)
{
	e->count = 0;
	e->i_champ = 1;
	turn_over(e);
	return (0);
}
