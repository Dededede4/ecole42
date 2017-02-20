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

t_bool		is_free(t_room *room, t_way	*way)
{
	t_way	*current;

	current = way;
	while(current)
	{
		if ((*(t_room**)current->content) == room)
			return FALSE;
		current = current->next;
	}
	return TRUE;
}

t_bool		usedway(t_way *way)
{
	while (way)
	{
		if ((*(t_room**)way->content)->have_way == TRUE)
			return (TRUE);
		way = way->next;
	}
	return (FALSE);
}

t_way 	*get_next_way(t_antler *antler, t_ways *way)
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
	return (newways);
}

t_way	*find_sortest_way(t_antler *antler, int	*way_no)
{
	t_ways	*ways;
	t_ways	*futureways;
	t_way	*way;
	t_way	*way_return;
	int		i;

	i = 1;
	way = ft_lstnew(&antler->start, sizeof(void*));
	ways = get_next_way(antler, way);
	/*
	t_ways est une liste chaînée
	dont le content est un pointeur vers t_way
	dont le content est un pointeur vers room
	*/
	futureways = NULL;
		
	while (ways)
	{
		way = (*(t_way**)ways->content);
		futureways = get_next_way(antler, way);
		way_return = way;
		if (way && *way_no < i)
		{
			while (way->next)
				way = way->next;
			if ((*(t_room**)(way->content)) == antler->end)
			{
				/* La route la plus courte, ne pas oublier de free */
				*way_no = i;
				return (way_return);
			}
		}
		i++;
		ft_lstadd_end(&ways, futureways);
		ways = ways->next;
	}
	*way_no = -1;
	return (NULL);
}

t_ways	*find_sortest_ways(t_antler *antler)
{
	t_way	*way;
	t_ways	*ways;
	t_ways	*ways_first;
	int		way_no;

	ft_printf("La route la plus courte est :\n");
	ways = NULL;
	way_no = 0;
	while ((way = find_sortest_way(antler, &way_no)))
	{
		if (usedway(way))
			continue;
		ft_lstadd_end(&ways, ft_lstnew(&way, sizeof(void*)));
		while (way)
		{
			if ((*(t_room**)(way->content)) != antler->start && (*(t_room**)(way->content)) != antler->end)
				(*(t_room**)(way->content))->have_way = TRUE;
			way = way->next;
		}
	}
	ways_first = ways;
	while (ways)
	{
		way = (*(t_way**)ways->content);
		while (way)
		{
			ft_printf("%s -> ", (*(t_room**)(way->content))->name);
			way = way->next;
		}
		ft_printf("\n");
		ways = ways->next;
	}
	return (ways);
}

int		main(void)
{
	t_antler	*antler;
	


	if(!(antler = lemin_parser()))
		return (0);
	find_sortest_ways(antler);
	lemin_output(antler);
}
