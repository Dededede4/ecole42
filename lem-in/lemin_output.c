/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lemin_output.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mprevot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/17 17:22:17 by mprevot           #+#    #+#             */
/*   Updated: 2017/02/17 17:22:18 by mprevot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

void	lemin_output(t_antler	*antler)
{
	t_room		*cur_room;
	t_pipe		*cur_pipe;
	char		*str;

	cur_room = antler->rooms;
	cur_pipe = antler->pipes;
	ft_printf("Fourmies : %i\n", antler->ant_nbr_global);
	if (antler->start)
		ft_printf("Start : %s\n", antler->start->name);
	if (antler->end)
		ft_printf("End : %s\n", antler->end->name);
	while (cur_room)
	{
		str = ft_room2str(cur_room);
		ft_printf("%s\n", str);
		free(str);
		cur_room = cur_room->next;
	}
	while (cur_pipe)
	{
		str = ft_pipe2str(cur_pipe);
		ft_printf("%s\n", str);
		free(str);
		cur_pipe = cur_pipe->next;
	}
}