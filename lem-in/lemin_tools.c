/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lemin_tools.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mprevot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/17 14:23:43 by mprevot           #+#    #+#             */
/*   Updated: 2017/02/17 14:23:49 by mprevot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

char	*ft_room2str(t_room *room)
{
	return ft_strjoin_multi(TRUE, ft_strdup(room->name), ft_strdup(" "),
		ft_itoa(room->x), ft_strdup(" "), ft_itoa(room->y), NULL);
}

char	*ft_pipe2str(t_pipe *pipe)
{
	return ft_strjoin_multi(FALSE, pipe->a->name, "-",
		pipe->b->name, NULL);
}

t_room	*ft_findroom(char	*name, t_antler *antler)
{
	t_room	*room;

	room = antler->rooms;
	while (room)
	{
		if (ft_strcmp(room->name, name) == 0)
			return (room);
		room = room->next;
	}
	return (NULL);
}