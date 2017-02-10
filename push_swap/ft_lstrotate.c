/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstrotate.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mprevot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/10 14:47:28 by mprevot           #+#    #+#             */
/*   Updated: 2017/02/10 14:47:39 by mprevot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void		ft_lstrotate(t_list **lst)
{
	t_list	*first;
	t_list	*current;

	first = *lst;
	current = first;
	while (current->next)
		current = current->next;
	*lst = first->next;
	current->next = first;
	first->next = NULL;
}
