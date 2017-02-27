/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lemin_moves.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mprevot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/27 15:07:49 by mprevot           #+#    #+#             */
/*   Updated: 2017/02/27 15:07:52 by mprevot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

void		move_ants(t_way *way)
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

t_bool		isended(t_way *way)
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

void		send_positives(t_antler *antler, t_way *way,
	t_bool *have_print, int *last_no)
{
	move_ants(way);
	(*last_no)++;
	(*((t_room**)way->content))->ant_no = *last_no;
	antler->ant_nbr_start--;
	if (!isended(way) && ft_printmoves_positives(way))
		*have_print = TRUE;
}

void		send_negatives(t_way *way, t_bool *have_print)
{
	move_ants(way);
	(*((t_room**)way->content))->ant_no = -1;
	if (!isended(way) && ft_printmoves_negatives(way))
		*have_print = TRUE;
}

t_bool		send_ants(t_antler *antler, t_ways *ways, int *last_no)
{
	t_way	*way;
	t_bool	isfirst;
	t_bool	have_print;

	isfirst = TRUE;
	have_print = FALSE;
	while (ways)
	{
		way = (*((t_way**)ways->content))->next;
		if ((ft_lstlen(way) <= antler->ant_nbr_start || isfirst)
			&& antler->ant_nbr_start != 0)
			send_positives(antler, way, &have_print, last_no);
		else if (antler->ant_nbr_start == 0)
			send_negatives(way, &have_print);
		isfirst = FALSE;
		ways = ways->next;
	}
	ft_printf((have_print) ? "\n" : "");
	return (1);
}
