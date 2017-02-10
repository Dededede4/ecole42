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

int		main(int argc, char **argv)
{
	t_list		*lst;
	t_stacks	*selectsort;
	t_stacks	*quicksort;
	int			len_selectsort;
	int			len_quicksort;

	if (argc > 1)
	{
		lst = ft_arraytolst(argv + 1, argc - 1);
		quicksort = ft_pushswap_quicksort(lst);
		selectsort = ft_pushswap_selectsort(lst);
		len_quicksort = ft_lstlen(quicksort->instructs);
		len_selectsort = ft_lstlen(selectsort->instructs);
		if (len_selectsort <= len_quicksort)
			ft_printlst_str(selectsort->instructs);
		else
			ft_printlst_str(quicksort->instructs);
	}
	return (0);
}
