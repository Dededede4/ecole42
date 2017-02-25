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

void	move_ants(t_way *way)
{
	int		last_no;
	int		no;

	last_no = 0;
	while (way)
	{
		no = (*((t_room**)way->content))->ant_no;
		(*((t_room**)way->content))->ant_no = last_no;
		last_no = no;
		way = way->next;
	}
}

void		ft_printmoves_positives(t_way 	*way)
{
	if (!((*((t_room**)way->content))->ant_no))
		return ;
	if (way->next)
		ft_printmoves_positives(way->next);
	ft_printf("L%i-%s ", (*((t_room**)way->content))->ant_no, (*((t_room**)way->content))->name);
}

void		ft_printmoves_negatives(t_way 	*way)
{
	if ((*((t_room**)way->content))->ant_no == 0)
		return ;
	if (way->next)
		ft_printmoves_negatives(way->next);
	if ((*((t_room**)way->content))->ant_no != -1)
		ft_printf("L%i-%s ", (*((t_room**)way->content))->ant_no, (*((t_room**)way->content))->name);
}

t_bool	isended(t_way *way)
{
	way = way->next;
	while (way)
	{
		if ((*((t_room**)way->content))->ant_no != -1)
			return (FALSE);
		way = way->next;
	}
	return (TRUE);
}

t_bool		send_ants(t_antler *antler, t_ways	*ways, int *last_no)
{
	t_way 	*way;
	int		len;
	t_bool	isfirst;
	t_bool	have_print;
	//int		nbr_used_path;

	isfirst = TRUE;
	have_print = FALSE;
	while (ways)
	{
		way = (*((t_way**)ways->content))->next;
		len = ft_lstlen(way);
		if ((len <= (int)antler->ant_nbr_start || isfirst) && antler->ant_nbr_start != 0)
		{
			move_ants(way);
			(*last_no)++;
			(*((t_room**)way->content))->ant_no = *last_no;
			antler->ant_nbr_start--;
			if (!isended(way))
			{
				ft_printmoves_positives(way);
				have_print = TRUE;
			}
		}
		else if (antler->ant_nbr_start == 0)
		{
			move_ants(way);
			(*((t_room**)way->content))->ant_no = -1;
			if (!isended(way))
			{
				ft_printmoves_negatives(way);
				have_print = TRUE;
			}
		}
		isfirst = FALSE;
		ways = ways->next;
	}
	if (have_print)
		ft_printf("\n");
	return (1);
}



int		main(void)
{
	t_antler	*antler;
	t_ways		*ways;
	t_ways		*current;
	int			nbr;
	
	if(!(antler = lemin_parser()))
		return (0);
	ways = find_sortest_ways(antler);
	if (!ways)
		error();
	ft_printf("%d\n%s\n", antler->ant_nbr_global, antler->input);
	nbr = 0;
	while (!isended((*((t_way**)ways->content))))
		send_ants(antler, ways, &nbr);
	
	
	current = ways;
	while (current)
	{
		freelst((t_way**)current->content);
		current = current->next;
	}
	freelst(&ways);

	t_pipe *current_pipe;
	t_pipe *next_pipe;

	t_room *current_room;
	t_room *next_room;

	current_pipe = antler->pipes;
	while (current_pipe)
	{
		next_pipe = current_pipe->next;
		free(current_pipe);
		current_pipe = next_pipe;
	}

	current_room = antler->rooms;
	while (current_room)
	{
		next_room = current_room->next;
		free(current_room->name);
		free(current_room);
		current_room = next_room;
	}
	free(antler->input);
	free(antler);
	return (0);
}

/*

typedef struct			s_antler
{
	size_t				ant_nbr_global;
	size_t				ant_nbr_start;
	size_t				ant_nbr_end;


	struct s_pipe		*pipes;
	struct s_room		*rooms;
	struct s_room		*start;
	struct s_room		*end;

	struct s_way		*ways;	
}						t_antler;

*/











