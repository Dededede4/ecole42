/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pushswap_instructs_s.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mprevot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/10 15:27:36 by mprevot           #+#    #+#             */
/*   Updated: 2017/02/10 15:27:40 by mprevot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void		ft_pushswap_sa(t_stacks *stacks)
{
	if (stacks->stacka == NULL || stacks->stacka->next == NULL)
		return ;
	ft_instructnew(stacks, "sa");
	ft_swap(stacks->stacka->content, stacks->stacka->next->content);
}

void		ft_pushswap_sb(t_stacks *stacks)
{
	if (stacks->stackb == NULL || stacks->stackb->next == NULL)
		return ;
	ft_instructnew(stacks, "sb");
	ft_swap(stacks->stackb->content, stacks->stackb->next->content);
}

void		ft_pushswap_ss(t_stacks *stacks)
{
	t_bool	used;

	used = FALSE;
	if (stacks->stacka && stacks->stacka->next != NULL)
	{
		ft_swap(stacks->stacka->content, stacks->stacka->next->content);
		used = TRUE;
	}
	if (stacks->stackb && stacks->stackb->next != NULL)
	{
		ft_swap(stacks->stackb->content, stacks->stackb->next->content);
		used = TRUE;
	}
	if (used)
		ft_instructnew(stacks, "ss");
}
