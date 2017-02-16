/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pushswap_instructs_simplificator.c              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mprevot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/14 18:51:19 by mprevot           #+#    #+#             */
/*   Updated: 2017/02/14 18:51:22 by mprevot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int				ft_pushswap_instructs_simplificator_del(
	t_instructs **lst, char *str1, char *str2)
{
	t_instructs	*current;
	t_instructs	*precedent;

	current = *lst;
	precedent = NULL;
	while (current && current->next)
	{
		if (ft_strcmp(current->content, str1) == 0 &&
			ft_strcmp(current->next->content, str2) == 0)
		{
			if (precedent)
				precedent->next = current->next->next;
			else
				*lst = current->next->next;
			free(current->content);
			free(current->next->content);
			free(current->next);
			free(current);
			return (1);
		}
		precedent = current;
		current = current->next;
	}
	return (0);
}

void			ft_pushswap_instructs_simplificator(t_instructs **lst)
{
	int			o;

	o = 1;
	while (o)
	{
		o = 0;
		o += ft_pushswap_instructs_simplificator_del(lst, "pa", "pb");
		o += ft_pushswap_instructs_simplificator_del(lst, "pb", "pa");
		o += ft_pushswap_instructs_simplificator_del(lst, "ra", "rra");
		o += ft_pushswap_instructs_simplificator_del(lst, "rra", "ra");
		o += ft_pushswap_instructs_simplificator_del(lst, "rb", "rrb");
		o += ft_pushswap_instructs_simplificator_del(lst, "rrb", "rb");
		o += ft_pushswap_instructs_simplificator_del(lst, "rr", "rrr");
		o += ft_pushswap_instructs_simplificator_del(lst, "rrr", "rr");
	}
}
