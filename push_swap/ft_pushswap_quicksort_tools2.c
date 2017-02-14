/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pushswap_quicksort_tools2.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mprevot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/14 19:09:15 by mprevot           #+#    #+#             */
/*   Updated: 2017/02/14 19:09:27 by mprevot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void		ft_pushswap_quicksort_fixgoodposition_a(
	t_vals **fixeds, t_vals *lst, int start)
{
	t_vals	*sorted;
	t_vals	*sorted_first;
	int		p;

	sorted = ft_lstsort(lst);
	sorted_first = sorted;
	p = *((int*)lst->content);
	while (lst)
	{
		if (start-- < 0 && (ft_pushswap_quicksort_isfixed(*fixeds, p))
			&& *((int*)lst->content) == *((int*)sorted->content))
			ft_pushswap_quicksort_setfixed(fixeds, *((int*)lst->content));
		p = *((int*)lst->content);
		lst = lst->next;
		sorted = sorted->next;
	}
	ft_freetvals(&sorted_first);
}

void		ft_pushswap_quicksort_fixgoodposition_b(
	t_vals **fixeds, t_vals *lst, int start)
{
	t_vals	*sorted;
	t_vals	*sorted_first;
	int		p;

	sorted = ft_lstsort_rev(lst);
	sorted_first = sorted;
	p = *((int*)lst->content);
	while (lst)
	{
		if (start-- < 0 && (ft_pushswap_quicksort_isfixed(*fixeds, p))
			&& *((int*)lst->content) == *((int*)sorted->content))
			ft_pushswap_quicksort_setfixed(fixeds, *((int*)lst->content));
		p = *((int*)lst->content);
		lst = lst->next;
		sorted = sorted->next;
	}
	ft_freetvals(&sorted_first);
}
