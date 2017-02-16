/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mprevot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/10 14:19:45 by mprevot           #+#    #+#             */
/*   Updated: 2017/02/10 14:19:46 by mprevot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void			ft_freestacks(t_stacks **s)
{
	if (*s == NULL)
		return ;
	ft_freetvals(&((*s)->instructs));
	ft_freetvals(&((*s)->stacka));
	ft_freetvals(&((*s)->stackb));
	free(*s);
	*s = NULL;
}

t_stacks		*ft_pushswap_bestinstructs(t_list *lst)
{
	t_stacks	*a;
	t_stacks	*b;
	int			len_a;
	int			len_b;

	a = ft_pushswap_quicksort(lst);
	len_a = ft_lstlen(a->instructs);
	b = ft_pushswap_selectsort(lst);
	len_b = ft_lstlen(b->instructs);
	if (len_a > len_b)
	{
		ft_freestacks(&a);
		a = b;
		len_a = len_b;
		b = NULL;
	}
	else
		ft_freestacks(&b);
	b = (len_a < 100) ? ft_pushswap_bublesort(lst) : b;
	len_b = (b) ? ft_lstlen(b->instructs) : INT_MAX;
	if (len_a > len_b)
		ft_freestacks(&a);
	else if (b)
		ft_freestacks(&b);
	return ((len_a <= len_b) ? a : b);
}

int				main(int argc, char **argv)
{
	t_list		*lst;
	t_stacks	*best;

	if (argc <= 2)
		return (0);
	lst = ft_arraytolst(argv + 1, argc - 1);
	best = ft_pushswap_bestinstructs(lst);
	ft_printlst_str(best->instructs);
	ft_freestacks(&best);
	ft_freetvals(&lst);
	return (0);
}
