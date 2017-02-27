/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lemin_finder.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mprevot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/27 12:32:55 by mprevot           #+#    #+#             */
/*   Updated: 2017/02/27 12:32:57 by mprevot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

t_ways	*get_next_way(t_antler *antler, t_way *way)
{
	t_pipe		*pcurrent;
	t_room		*room;
	t_room		*room_next;
	t_ways		*newways;
	t_ways		*newway;

	pcurrent = antler->pipes;
	room = (*(t_room**)ft_lstlast(way)->content);
	newways = NULL;
	newway = ft_lstcpy(way);
	while (pcurrent)
	{
		room_next = NULL;
		room_next = (pcurrent->a == room) ? pcurrent->b : room_next;
		room_next = (pcurrent->b == room) ? pcurrent->a : room_next;
		if (room_next && is_free(room_next, way))
		{
			ft_lstadd_end(&newway, ft_lstnew(&room_next, sizeof(void*)));
			ft_lstadd_end(&newways, ft_lstnew(&newway, sizeof(void*)));
			newway = ft_lstcpy(way);
		}
		pcurrent = pcurrent->next;
	}
	freelst(&newway);
	return (newways);
}

t_way	*find_sortest_way_return(t_way *way_return, t_ways *first_ways)
{
	t_way	*cpy;
	t_ways	*ways;
	t_way	*way;

	cpy = ft_lstcpy(way_return);
	ways = first_ways;
	while (ways)
	{
		way = (*(t_way**)ways->content);
		freelst(&way);
		ways = ways->next;
	}
	freelst(&first_ways);
	return (cpy);
}

t_way	*find_sortest_way(t_antler *antler, int *way_no)
{
	t_ways	*ways;
	t_way	*way;
	t_way	*way_return;
	t_ways	*first_ways;
	int		i;

	i = 1;
	way = ft_lstnew(&antler->start, sizeof(void*));
	ways = get_next_way(antler, way);
	freelst(&way);
	first_ways = ways;
	while (ways && (way = (*(t_way**)ways->content)))
	{
		ft_lstadd_end(&first_ways, get_next_way(antler, way));
		way_return = way;
		if (way && *way_no < i++)
			if ((*(t_room**)(ft_lstlast(way)->content)) == antler->end
				&& (*way_no = i))
				return (find_sortest_way_return(way_return, first_ways));
		ways = ways->next;
	}
	*way_no = -1;
	return (find_sortest_way_return(NULL, first_ways));
}

t_ways	*find_sortest_ways(t_antler *antler)
{
	t_way	*way;
	t_ways	*ways;
	int		way_no;

	ways = NULL;
	way_no = 0;
	while ((way = find_sortest_way(antler, &way_no)))
	{
		if (usedway(way))
		{
			freelst(&way);
			continue;
		}
		ft_lstadd_end(&ways, ft_lstnew(&way, sizeof(void*)));
		while (way)
		{
			if ((*(t_room**)(way->content)) != antler->start
				&& (*(t_room**)(way->content)) != antler->end)
				(*(t_room**)(way->content))->have_way = TRUE;
			way = way->next;
		}
	}
	return (ways);
}
