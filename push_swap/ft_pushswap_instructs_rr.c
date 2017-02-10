/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pushswap_instructs_rr.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mprevot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/10 15:27:15 by mprevot           #+#    #+#             */
/*   Updated: 2017/02/10 15:27:22 by mprevot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void		ft_pushswap_rra(t_stacks *stacks)
{
	if (!stacks->stacka || !stacks->stacka->next)
		return ;
	ft_lstrotate_reverse(&(stacks->stacka));
	ft_instructnew(stacks, "rra");
}

void		ft_pushswap_rrb(t_stacks *stacks)
{
	if (!stacks->stackb || !stacks->stackb->next)
		return ;
	ft_lstrotate_reverse(&(stacks->stackb));
	ft_instructnew(stacks, "rrb");
}

void		ft_pushswap_rrr(t_stacks *stacks)
{
	if (stacks->stacka && stacks->stacka->next)
		ft_lstrotate_reverse(&(stacks->stacka));
	if (stacks->stackb && stacks->stackb->next)
		ft_lstrotate_reverse(&(stacks->stackb));
	if ((stacks->stacka && stacks->stacka->next) ||
		(stacks->stackb && stacks->stackb->next))
		ft_instructnew(stacks, "rrr");
}
