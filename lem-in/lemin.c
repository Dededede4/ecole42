/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem-in.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mprevot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/17 17:17:50 by mprevot           #+#    #+#             */
/*   Updated: 2017/02/17 17:17:52 by mprevot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

int		main(void)
{
	t_antler	*antler;
	t_ways		*ways;
	int			nbr;

	if (!(antler = lemin_parser()))
		return (0);
	ways = find_sortest_ways(antler);
	if (!ways)
		error();
	ft_printf("%d\n%s\n", antler->ant_nbr_global, antler->input);
	nbr = 0;
	while (!isended((*((t_way**)ways->content))))
		send_ants(antler, ways, &nbr);
	exit(0);
}
