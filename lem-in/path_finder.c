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

void	freelst(t_way **ways)
{
	t_ways	*current;
	t_ways	*next;

	current = *ways;
	while (current)
	{
		next = current->next;
		free(current->content);
		free(current);
		current = next;
	}
	*ways = NULL;
}

t_ways 	*get_next_way(t_antler *antler, t_ways *ways)
{
	t_pipe *pcurrent;
	t_room 		*room;
	t_room 		*room_next;
	t_ways		*newways;
	t_ways		*newway;
	t_ways		*current;
	t_ways		*next;
	t_way 		*way;
	t_list		*test;

	pcurrent = antler->pipes;
	current = ways;
	while(current->next)
		current = current->next;
	room = (*(t_room**)current->content);
	newways = NULL; 
	newway = ft_lstcpy(ways);
	while (pcurrent)
	{
		room_next = NULL;
		if (pcurrent->a == room)
			room_next = pcurrent->b;
		if (pcurrent->b == room)
			room_next = pcurrent->a;
		if (room_next && is_free(room_next, ways))
		{
			ft_lstadd_end(&newway, ft_lstnew(&room_next, sizeof(void*)));
			ft_lstadd_end(&newways, ft_lstnew(&newway, sizeof(void*)));
			newway = ft_lstcpy(ways);
		}

		pcurrent = pcurrent->next;
	}
	current = ways;
	while (current)
	{
		next = current->next;
		way = *((t_way**)current->content);
		test = (*(t_list**)way->content);
		ft_printf("bite : %s\n", (*((t_room**)(test->content)))->name);
		freelst(&current);
		current = next;
	}
	freelst(&ways);
	return (newways);
}

t_way	*find_sortest_way(t_antler *antler, int	*way_no)
{
	t_ways	*ways;
	t_ways	*futureways;
	t_way	*way;
	t_way	*way_return;
	t_ways	*first_ways;
	t_way 	*cpy;
	int		i;

	i = 1;
	way = ft_lstnew(&antler->start, sizeof(void*));
	ways = get_next_way(antler, way);
	freelst(&way);
	first_ways = ways;
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
				cpy = ft_lstcpy(way_return);
				freelst(&first_ways);
				freelst(&futureways);
				return (way_return);
			}
		}
		freelst(&way);
		i++;
		ft_lstadd_end(&ways, futureways);
		ways = ways->next;
	}
	*way_no = -1;
	freelst(&first_ways);
				freelst(&futureways);
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
	return (ways_first);
}