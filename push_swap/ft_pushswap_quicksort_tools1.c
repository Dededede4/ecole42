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

int			ft_pushswap_quicksort_mediane(t_vals *fixeds, t_vals *lst)
{
	int		i;
	int		len;
	t_vals	*sorted;
	t_vals	*first;

	len = 0;
	i = 0;
	first = lst;
	while (lst)
	{
		if (ft_pushswap_quicksort_isfixed(fixeds, (*((int*)lst->content))))
			break ;
		len++;
		lst = lst->next;
	}
	sorted = ft_lstsort(ft_lstcpy_max(first, len));
	while (len / 2 && sorted->next
		&& !ft_pushswap_quicksort_isfixed(fixeds, (*((int*)sorted->content))))
	{
		if (i == len / 2)
			return (*((int*)sorted->content));
		i++;
		sorted = sorted->next;
	}
	return (*((int*)first->content));
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
