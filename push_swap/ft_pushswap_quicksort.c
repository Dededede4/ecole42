/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pushswap_quicksort.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mprevot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/08 17:04:32 by mprevot           #+#    #+#             */
/*   Updated: 2017/02/08 17:04:34 by mprevot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void			ft_pushswap_quicksort_a2b_push(t_stacks *stacks, int nbr)
{
	int			len;
	int			pos;
	int			moves;
	t_vals		*lst;

	pos = 0;
	lst = stacks->stacka;
	len = ft_lstlen(lst);
	while (lst && *((int*)lst->content) != nbr)
	{
		pos++;
		lst = lst->next;
	}
	moves = (pos > (len / 2)) ? pos - len : pos;
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

void			ft_pushswap_quicksort_a2b(t_stacks *stacks, t_vals **f_nbrs)
{
	int			pivot;
	t_vals		*current;
	t_vals		*current_first;
	int			last;

	while (stacks->stacka)
	{
		last = ft_pushswap_quicksort_findmin(stacks->stacka);
		if (!(ft_pushswap_quicksort_isfixed(*f_nbrs, last)))
			break ;
		ft_pushswap_quicksort_a2b_push(stacks, last);
	}
	if (stacks->stacka == NULL || !(current = ft_lstcpy(stacks->stacka)))
		return ;
	pivot = ft_pushswap_quicksort_mediane(*f_nbrs, stacks->stacka);
	current_first = current;
	while (current)
	{
		if (*((int*)current->content) < pivot)
			ft_pushswap_quicksort_a2b_push(stacks, *((int*)current->content));
		current = current->next;
	}
	ft_freetvals(&current_first);
	ft_pushswap_quicksort_setfixed(f_nbrs, pivot);
	ft_pushswap_quicksort_a2b_push(stacks, pivot);
}

void			ft_pushswap_quicksort_b2a_push(t_stacks *stacks, int nbr)
{
	int			len;
	int			pos;
	int			moves;
	t_vals		*lst;

	pos = 0;
	lst = stacks->stackb;
	len = ft_lstlen(lst);
	while (lst && *((int*)lst->content) != nbr)
	{
		pos++;
		lst = lst->next;
	}
	moves = (pos > (len / 2)) ? pos - len : pos;
	while (moves != 0)
	{
		if (moves > 0)
			ft_pushswap_instruct(INSTRUCT_RB, stacks);
		else
			ft_pushswap_instruct(INSTRUCT_RRB, stacks);
		moves += (moves > 0) ? -1 : 1;
	}
	ft_pushswap_instruct(INSTRUCT_PA, stacks);
}

void			ft_pushswap_quicksort_b2a(t_stacks *stacks, t_vals **f_nbrs)
{
	int			pivot;
	t_vals		*current;
	t_vals		*current_first;
	int			last;

	while (stacks->stackb)
	{
		last = ft_pushswap_quicksort_findmax(stacks->stackb);
		if (!(ft_pushswap_quicksort_isfixed(*f_nbrs, last)))
			break ;
		ft_pushswap_quicksort_b2a_push(stacks, last);
	}
	if (stacks->stackb == NULL || !(current = ft_lstcpy(stacks->stackb)))
		return ;
	pivot = ft_pushswap_quicksort_mediane(*f_nbrs, stacks->stackb);
	current_first = current;
	while (current)
	{
		if (*((int*)current->content) > pivot)
			ft_pushswap_quicksort_b2a_push(stacks, *((int*)current->content));
		current = current->next;
	}
	ft_freetvals(&current_first);
	ft_pushswap_quicksort_setfixed(f_nbrs, pivot);
	ft_pushswap_quicksort_b2a_push(stacks, pivot);
}

t_stacks		*ft_pushswap_quicksort(t_vals *vals)
{
	t_stacks	*stacks;
	t_vals		*f_nbrs;
	size_t		len;

	f_nbrs = NULL;
	stacks = malloc(sizeof(t_stacks));
	stacks->stacka = ft_lstcpy(vals);
	stacks->stackb = NULL;
	stacks->instructs = NULL;
	len = ft_lstlen(stacks->stacka);
	while (!ft_intlst_issorted(stacks->stacka) && len != ft_lstlen(f_nbrs))
	{
		ft_pushswap_quicksort_fixalones(&f_nbrs, stacks->stacka);
		ft_pushswap_quicksort_fixgoodposition_a(&f_nbrs, stacks->stacka, 0);
		while (stacks->stacka)
			ft_pushswap_quicksort_a2b(stacks, &f_nbrs);
		ft_pushswap_quicksort_fixalones(&f_nbrs, stacks->stackb);
		ft_pushswap_quicksort_fixgoodposition_b(&f_nbrs, stacks->stackb, 0);
		while (stacks->stackb)
			ft_pushswap_quicksort_b2a(stacks, &f_nbrs);
	}
	ft_freetvals(&f_nbrs);
	ft_pushswap_instructs_simplificator(&stacks->instructs);
	return (stacks);
}
