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

t_bool		send_ants(t_antler *antler, t_ways	*ways, int *last_no)
{
	t_way 	*way;
	int		len;
	t_bool	isfirst;
	//int		nbr_used_path;

	isfirst = TRUE;
	while (ways)
	{
		way = (*((t_way**)ways->content))->next;
		len = ft_lstlen(way);
		if (len <= (int)antler->ant_nbr_start || isfirst)
		{
			move_ants(way);
			(*last_no)++;
			(*((t_room**)way->content))->ant_no = *last_no;
			antler->ant_nbr_start--;
			while (way && (*((t_room**)way->content))->ant_no)
			{
				ft_printf("L%i-%s ", (*((t_room**)way->content))->ant_no, (*((t_room**)way->content))->name);
				way = way->next;
			}
		}
		else
		{
			move_ants(way);
			(*((t_room**)way->content))->ant_no = -1;
			while (way)
			{
				if ((*((t_room**)way->content))->ant_no != -1 && (*((t_room**)way->content))->ant_no != 0)
					ft_printf("L%i-%s ", (*((t_room**)way->content))->ant_no, (*((t_room**)way->content))->name);
				way = way->next;
			}
		}
		isfirst = FALSE;
		ways = ways->next;
	}
	ft_printf("\n");
	return (1);
}

int		main(void)
{
	t_antler	*antler;
	t_ways		*ways;
	int			nbr;
	
	if(!(antler = lemin_parser()))
		return (0);
	ways = find_sortest_ways(antler);
	nbr = 0;
	while (antler->ant_nbr_start)
		send_ants(antler, ways, &nbr);
	lemin_output(antler);
}
