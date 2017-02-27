/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lemin_finder_tools.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mprevot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/27 18:09:32 by mprevot           #+#    #+#             */
/*   Updated: 2017/02/27 18:09:33 by mprevot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

t_bool		is_free(t_room *room, t_way *way)
{
	t_way	*current;

	current = way;
	while (current)
	{
		if ((*(t_room**)current->content) == room)
			return (FALSE);
		current = current->next;
	}
	return (TRUE);
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
