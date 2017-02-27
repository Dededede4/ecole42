/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lemin_parser_create.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mprevot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/27 18:03:02 by mprevot           #+#    #+#             */
/*   Updated: 2017/02/27 18:03:03 by mprevot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

t_room			*newroom(t_antler *antler, t_bool is_start, t_bool is_end)
{
	t_room		*room;

	if (!(room = malloc(sizeof(t_room))))
		error();
	if (is_start)
	{
		if (antler->start != NULL)
			error();
		antler->start = room;
	}
	if (is_end)
	{
		if (antler->end != NULL)
			error();
		antler->end = room;
	}
	room->have_way = FALSE;
	room->ant_no = 0;
	room->next = antler->rooms;
	room->name = "\0";
	antler->rooms = room;
	return (room);
}

t_antler		*newantler(void)
{
	t_antler	*antler;

	if (!(antler = malloc(sizeof(t_antler))))
		error();
	antler->rooms = NULL;
	antler->pipes = NULL;
	antler->input = ft_strdup("");
	antler->start = NULL;
	antler->end = NULL;
	return (antler);
}
