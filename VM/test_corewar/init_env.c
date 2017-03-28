/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntoniolo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/27 20:37:11 by ntoniolo          #+#    #+#             */
/*   Updated: 2017/03/28 00:33:23 by ntoniolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "script.h"

void		init_env(t_env *e, char **argv)
{
	ft_bzero(e, sizeof(t_env));
	e->dump = ft_atoi(argv[2]);
	e->nb_player = 32;
	e->rd.first = 0;
	ft_bzero(e->rd.tab, sizeof(int) * N);
	ft_bzero(e->cmd, 500);
	e->line = NULL;
	e->chr = NULL;
	e->i = 0;
	e->j = 0;
	e->b = 0;
	e->count = 0;
	e->y = 0;
	e->str_unit = 0;
	e->nb_test = 0;
}
