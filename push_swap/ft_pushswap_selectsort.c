/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pushswap_selectsort.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mprevot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/10 14:10:24 by mprevot           #+#    #+#             */
/*   Updated: 2017/02/10 14:10:26 by mprevot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int				ft_pushswap_selectsort_findmin(t_vals *vals)
{
	int			min_val;
	int			min_pos;
	int			length;

	if (!vals)
		return (0);
	length = 0;
	min_val = *((int*)vals->content);
	min_pos = 0;
	while (vals)
	{
		if (*((int*)vals->content) < min_val)
		{
			min_val = *((int*)vals->content);
			min_pos = length;
		}
		length++;
		vals = vals->next;
	}
	return (min_pos <= (length / 2) ? min_pos : 0 - (length - min_pos));
}

t_stacks		*ft_newstacks(t_vals *vals)
{
	t_stacks	*stacks;

	stacks = malloc(sizeof(t_stacks));
	stacks->stacka = ft_lstcpy(vals);
	stacks->instructs = NULL;
	stacks->stackb = NULL;
	return (stacks);
}

t_stacks		*ft_pushswap_selectsort(t_vals *vals)
{
	t_stacks	*stacks;
	int			moves;

	stacks = ft_newstacks(vals);
	while (stacks->stacka)
	{
		moves = ft_pushswap_selectsort_findmin(stacks->stacka);
		while (moves != 0)
		{
			if (moves > 0)
				ft_pushswap_instruct(INSTRUCT_RA, stacks);
			else
				ft_pushswap_instruct(INSTRUCT_RRA, stacks);
			moves += (moves > 0) ? -1 : 1;
		}
		ft_pushswap_instruct(INSTRUCT_PB, stacks);
	}
	while (vals)
	{
		ft_pushswap_instruct(INSTRUCT_PA, stacks);
		vals = vals->next;
	}
	ft_pushswap_instructs_simplificator(&stacks->instructs);
	return (stacks);
}
