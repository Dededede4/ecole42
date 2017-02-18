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

t_bool		is_free(t_room *room, t_wayroom	*way)
{
	t_wayroom	*current;

	current = way;
	while(current)
	{
		if ((*(t_room**)current->content) == room)
			return FALSE;
		current = current->next;
	}
	return TRUE;
}

t_wayroom 	*get_next_way(t_antler *antler, t_ways *way)
{
	t_pipe *pcurrent;
	//t_room *rcurrent;
	//
	t_room 		*room;
	t_room 		*room_next;
	t_ways		*newways;
	t_ways		*newway;
	t_ways		*current;

	pcurrent = antler->pipes;
	current = way;
	while(current->next)
		current = current->next;
	room = (*(t_room**)current->content);
	//ft_printf("Recherche des connexions pour : %s\n", room->name);
	newways = NULL; 
	newway = ft_lstcpy(way);
	while (pcurrent)
	{
		room_next = NULL;
		if (pcurrent->a == room)
			room_next = pcurrent->b;
		if (pcurrent->b == room)
			room_next = pcurrent->a;

		if (room_next && is_free(room_next, way))
		{
			//ft_printf("Trouvé : %s\n", room_next->name);
			ft_lstadd_end(&newway, ft_lstnew(&room_next, sizeof(void*)));
			ft_lstadd_end(&newways, ft_lstnew(&newway, sizeof(void*)));
			newway = ft_lstcpy(way);
		}

		pcurrent = pcurrent->next;
	}
	// free ways
	t_ways *test = newways;
	while(test)
	{
		//ft_printf("o ");
		test = test->next;
	}
	//ft_printf("\n");
	return (newways);
}

int		main(void)
{
	t_antler	*antler;
	t_ways	*ways;
	t_ways	*futureways;
	t_wayroom	*way;

	if(!(antler = lemin_parser()))
		return (0);

	way = ft_lstnew(&antler->start, sizeof(void*));
	ways = get_next_way(antler, way);
	ft_printf("\n\n");
	/*
	t_ways est une liste chaînée
	dont le content est un pointeur vers t_wayroom
	dont le content est un pointeur vers room
	*/
	futureways = NULL;
		
	while (ways)
	{
		way = (*(t_wayroom**)ways->content);
		futureways = get_next_way(antler, way);
		while (way)
		{
			ft_printf("%s -> ", (*(t_room**)(way->content))->name);
			way = way->next;
		}
		ft_lstadd_end(&ways, futureways);
		ways = ways->next;
		ft_printf("\n");
	}
	ft_printf("\n\n");
	lemin_output(antler);
}
