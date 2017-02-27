/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lemin_moves_print.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mprevot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/27 17:59:10 by mprevot           #+#    #+#             */
/*   Updated: 2017/02/27 17:59:11 by mprevot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

t_bool		ft_printmoves_positives(t_way *way)
{
	if (!((*((t_room**)way->content))->ant_no))
		return (TRUE);
	if (way->next)
		ft_printmoves_positives(way->next);
	ft_printf("L%i-%s ", (*((t_room**)way->content))->ant_no,
		(*((t_room**)way->content))->name);
	return (TRUE);
}

t_bool		ft_printmoves_negatives(t_way *way)
{
	if ((*((t_room**)way->content))->ant_no == 0)
		return (TRUE);
	if (way->next)
		ft_printmoves_negatives(way->next);
	if ((*((t_room**)way->content))->ant_no != -1)
		ft_printf("L%i-%s ", (*((t_room**)way->content))->ant_no,
			(*((t_room**)way->content))->name);
	return (TRUE);
}
