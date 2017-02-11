/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pushswap_instructs.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mprevot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/10 15:08:07 by mprevot           #+#    #+#             */
/*   Updated: 2017/02/10 15:08:09 by mprevot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void		ft_instructnew(t_stacks *stacks, char *instruct_str)
{
	t_instructs		*new;

	new = ft_lstnew(instruct_str, ft_strlen(instruct_str) + 1);
	ft_lstadd_end(&stacks->instructs, new);
}

int			ft_exit(t_stacks *stacks)
{
	ft_putstr_fd("Error\n", 1);
	ft_freetvals(&stacks->stacka);
	ft_freetvals(&stacks->stackb);
	ft_freetvals(&stacks->instructs);
	free(stacks);
	exit(0);
	return (1);
}

void		ft_pushswap_instruct(char instruct, t_stacks *stacks)
{
	if (instruct == INSTRUCT_SA)
		ft_pushswap_sa(stacks);
	else if (instruct == INSTRUCT_SB)
		ft_pushswap_sb(stacks);
	else if (instruct == INSTRUCT_SS)
		ft_pushswap_ss(stacks);
	else if (instruct == INSTRUCT_PA)
		ft_pushswap_pa(stacks);
	else if (instruct == INSTRUCT_PB)
		ft_pushswap_pb(stacks);
	else if (instruct == INSTRUCT_RA)
		ft_pushswap_ra(stacks);
	else if (instruct == INSTRUCT_RB)
		ft_pushswap_rb(stacks);
	else if (instruct == INSTRUCT_RRA)
		ft_pushswap_rra(stacks);
	else if (instruct == INSTRUCT_RRB)
		ft_pushswap_rrb(stacks);
	else if (instruct == INSTRUCT_RR)
		ft_pushswap_rr(stacks);
	else if (instruct == INSTRUCT_RRR)
		ft_pushswap_rrr(stacks);
	else if (ft_exit(stacks))
		return ;
}
