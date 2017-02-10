/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pushswap_quicksort_tools1.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mprevot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/10 13:14:26 by mprevot           #+#    #+#             */
/*   Updated: 2017/02/10 13:14:51 by mprevot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int			ft_pushswap_quicksort_getmediane
	(t_vals *fixeds, t_vals *first, int len)
{
	int		i;
	t_vals	*cpy;
	t_vals	*sorted;
	t_vals	*sorted_first;
	int		r;

	i = 0;
	cpy = ft_lstcpy_max(first, len);
	sorted = ft_lstsort(cpy);
	sorted_first = sorted;
	ft_freetvals(&cpy);
	while (len / 2 && sorted->next
		&& !ft_pushswap_quicksort_isfixed(fixeds, (*((int*)sorted->content))))
	{
		if (i == len / 2)
		{
			r = *((int*)sorted->content);
			ft_freetvals(&sorted_first);
			return (r);
		}
		i++;
		sorted = sorted->next;
	}
	ft_freetvals(&sorted_first);
	return (*((int*)first->content));
}

int			ft_pushswap_quicksort_mediane(t_vals *fixeds, t_vals *lst)
{
	int		len;
	t_vals	*first;

	len = 0;
	first = lst;
	while (lst)
	{
		if (ft_pushswap_quicksort_isfixed(fixeds, (*((int*)lst->content))))
			break ;
		len++;
		lst = lst->next;
	}
	return (ft_pushswap_quicksort_getmediane(fixeds, first, len));
}

void		ft_pushswap_quicksort_setfixed(t_vals **fixeds, int nbr)
{
	if (*fixeds == NULL)
		*fixeds = ft_lstnew(&nbr, sizeof(int));
	else
	{
		if (!ft_pushswap_quicksort_isfixed(*fixeds, nbr))
			ft_lstadd(fixeds, ft_lstnew(&nbr, sizeof(int)));
	}
}

t_bool		ft_pushswap_quicksort_isallfixed(t_vals **fixeds, t_vals *lst)
{
	while (lst)
	{
		if (!ft_pushswap_quicksort_isfixed(*fixeds, (*((int*)lst->content))))
		{
			return (FALSE);
		}
		lst = lst->next;
	}
	return (TRUE);
}

void		ft_pushswap_quicksort_fixalones(t_vals **fixeds, t_vals *lst)
{
	int length;
	int prec;

	length = -1;
	while (lst)
	{
		if (ft_pushswap_quicksort_isfixed(*fixeds, *((int*)lst->content)))
		{
			if (length == 1)
			{
				ft_pushswap_quicksort_setfixed(fixeds, prec);
			}
			length = 0;
		}
		else
		{
			length++;
		}
		prec = *((int*)lst->content);
		lst = lst->next;
	}
}
