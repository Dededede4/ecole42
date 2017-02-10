/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pushswap_instructs_r.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mprevot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/10 15:27:01 by mprevot           #+#    #+#             */
/*   Updated: 2017/02/10 15:27:09 by mprevot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void		ft_pushswap_ra(t_stacks *stacks)
{
	if (!stacks->stacka || !stacks->stacka->next)
		return ;
	ft_lstrotate(&(stacks->stacka));
	ft_instructnew(stacks, "ra");
}

void		ft_pushswap_rb(t_stacks *stacks)
{
	if (!stacks->stackb || !stacks->stackb->next)
		return ;
	ft_lstrotate(&(stacks->stackb));
	ft_instructnew(stacks, "rb");
}

void		ft_pushswap_rr(t_stacks *stacks)
{
	if (stacks->stacka && stacks->stacka->next)
		ft_lstrotate(&(stacks->stacka));
	if (stacks->stackb && stacks->stackb->next)
		ft_lstrotate(&(stacks->stackb));
	if ((stacks->stackb && stacks->stackb->next)
		|| (stacks->stacka && stacks->stacka->next))
		ft_instructnew(stacks, "rr");
}
