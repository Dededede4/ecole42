/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstrotate_reverse.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mprevot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/10 14:49:33 by mprevot           #+#    #+#             */
/*   Updated: 2017/02/10 14:49:35 by mprevot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void		ft_lstrotate_reverse(t_list **lst)
{
	t_list	*first;
	t_list	*current;
	t_list	*before_last;

	first = *lst;
	current = first;
	while (current->next)
	{
		before_last = current;
		current = current->next;
	}
	current->next = first;
	*lst = current;
	before_last->next = NULL;
}
