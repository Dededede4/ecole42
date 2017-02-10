/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pushswap_instructs_p.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mprevot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/10 15:26:14 by mprevot           #+#    #+#             */
/*   Updated: 2017/02/10 15:26:34 by mprevot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void		ft_pushswap_pa(t_stacks *stacks)
{
	t_vals	*tmp;

	if (stacks->stackb == NULL)
		return ;
	ft_instructnew(stacks, "pa");
	tmp = stacks->stackb->next;
	stacks->stackb->next = stacks->stacka;
	stacks->stacka = stacks->stackb;
	stacks->stackb = tmp;
}

void		ft_pushswap_pb(t_stacks *stacks)
{
	t_vals	*tmp;

	if (stacks->stacka == NULL)
		return ;
	ft_instructnew(stacks, "pb");
	tmp = stacks->stacka->next;
	stacks->stacka->next = stacks->stackb;
	stacks->stackb = stacks->stacka;
	stacks->stacka = tmp;
}
