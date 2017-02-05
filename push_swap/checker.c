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

#include "push_swap.c"

int     main(int argc, char **argv)
{
	t_vals	vals;
	char	*line;

	if (argc <= 1)
	{
		ft_putstr_fd(2, "Error\n");
		exit(0);
	}
	vals = ft_arraytolst(argv + 1, argc - 1);
	while (ft_gnl(0, &line))
	{
		if (ft_strcmp(line, "sa") == 0)
			ft_pushswap_instruct(INSTRUCT_SA, stacks);
		else if (ft_strcmp(line, "sb") == 0)
			ft_pushswap_instruct(INSTRUCT_SB, stacks);
		else if (ft_strcmp(line, "ss") == 0)
			ft_pushswap_instruct(INSTRUCT_SS, stacks);
		else if (ft_strcmp(line, "pa") == 0)
			ft_pushswap_instruct(INSTRUCT_PA, stacks);
		else if (ft_strcmp(line, "pb") == 0)
			ft_pushswap_instruct(INSTRUCT_PB, stacks);
		else if (ft_strcmp(line, "ra") == 0)
			ft_pushswap_instruct(INSTRUCT_RA, stacks);
		else if (ft_strcmp(line, "rb") == 0)
			ft_pushswap_instruct(INSTRUCT_RB, stacks);
		else if (ft_strcmp(line, "rr") == 0)
			ft_pushswap_instruct(INSTRUCT_RR, stacks);
		else if (ft_strcmp(line, "rra") == 0)
			ft_pushswap_instruct(INSTRUCT_RRA, stacks);
		else if (ft_strcmp(line, "rrb") == 0)
			ft_pushswap_instruct(INSTRUCT_RRB, stacks);
		else if (ft_strcmp(line, "rrr") == 0)
			ft_pushswap_instruct(INSTRUCT_RRR, stacks);
	}	
}
