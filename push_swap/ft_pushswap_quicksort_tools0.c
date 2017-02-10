/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pushswap_quicksort_tools0.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mprevot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/10 13:47:51 by mprevot           #+#    #+#             */
/*   Updated: 2017/02/10 13:47:53 by mprevot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

t_bool			ft_pushswap_quicksort_isfixed(t_vals *fixeds, int nbr)
{
	while (fixeds)
	{
		if (*((int*)fixeds->content) == nbr)
			return (TRUE);
		fixeds = fixeds->next;
	}
	return (FALSE);
}

t_vals			*ft_pushswap_quicksort_findfirst(t_vals *fixeds, t_vals *lst)
{
	while (lst)
	{
		if (!(ft_pushswap_quicksort_isfixed(fixeds, (*((int*)lst->content)))))
		{
			return (lst);
		}
		lst = lst->next;
	}
	return (NULL);
}

int				ft_pushswap_quicksort_findlast(t_vals *fixeds, t_vals *lst)
{
	t_vals	*before_last;

	before_last = NULL;
	while (lst)
	{
		if (ft_pushswap_quicksort_isfixed(fixeds, (*((int*)lst->content))))
			return (*((int*)before_last->content));
		before_last = lst;
		lst = lst->next;
	}
	return (*((int*)before_last->content));
}

int				ft_pushswap_quicksort_findmin(t_vals *lst)
{
	int min;

	min = (*((int*)lst->content));
	while (lst)
	{
		if (min > (*((int*)lst->content)))
			min = (*((int*)lst->content));
		lst = lst->next;
	}
	return (min);
}

int				ft_pushswap_quicksort_findmax(t_vals *lst)
{
	int max;

	max = (*((int*)lst->content));
	while (lst)
	{
		if (max < (*((int*)lst->content)))
			max = (*((int*)lst->content));
		lst = lst->next;
	}
	return (max);
}
