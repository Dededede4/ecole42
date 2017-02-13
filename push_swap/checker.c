/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mprevot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/05 13:31:02 by mprevot           #+#    #+#             */
/*   Updated: 2017/02/05 13:58:59 by mprevot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int				ft_instructs_str2int(char *instruct)
{
	if (ft_strcmp(instruct, "sa") == 0)
		return (INSTRUCT_SA);
	else if (ft_strcmp(instruct, "sb") == 0)
		return (INSTRUCT_SB);
	else if (ft_strcmp(instruct, "ss") == 0)
		return (INSTRUCT_SS);
	else if (ft_strcmp(instruct, "pa") == 0)
		return (INSTRUCT_PA);
	else if (ft_strcmp(instruct, "pb") == 0)
		return (INSTRUCT_PB);
	else if (ft_strcmp(instruct, "ra") == 0)
		return (INSTRUCT_RA);
	else if (ft_strcmp(instruct, "rb") == 0)
		return (INSTRUCT_RB);
	else if (ft_strcmp(instruct, "rr") == 0)
		return (INSTRUCT_RR);
	else if (ft_strcmp(instruct, "rra") == 0)
		return (INSTRUCT_RRA);
	else if (ft_strcmp(instruct, "rrb") == 0)
		return (INSTRUCT_RRB);
	else if (ft_strcmp(instruct, "rrr") == 0)
		return (INSTRUCT_RRR);
	return (0);
}

void			ft_wait_instructs(t_stacks *stacks)
{
	char		*line;

	while (ft_gnl(0, &line))
	{
		ft_pushswap_instruct(ft_instructs_str2int(line), stacks);
		free(line);
	}
}

int				main(int argc, char **argv)
{
	t_vals		*vals;
	t_stacks	*stacks;

	if (argc <= 1)
		exit(0);
	vals = ft_arraytolst(argv + 1, argc - 1);
	stacks = malloc(sizeof(t_stacks));
	if (!stacks)
		return (0);
	stacks->stacka = vals;
	stacks->instructs = NULL;
	stacks->stackb = NULL;
	ft_wait_instructs(stacks);
	if (ft_intlst_issorted(stacks->stacka) && stacks->stackb == NULL)
		ft_printf("OK\n");
	else
		ft_printf("KO\n");
	ft_freetvals(&stacks->stacka);
	ft_freetvals(&stacks->stackb);
	ft_freetvals(&stacks->instructs);
	free(stacks);
	return (0);
}
