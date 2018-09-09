/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc_nopage_list.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mprevot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/08 22:26:41 by mprevot           #+#    #+#             */
/*   Updated: 2018/09/08 22:26:52 by mprevot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

t_list	*malloc_nopage_list(size_t size, t_list **container)
{
	t_list *current;

	current = *container;
	while (current->next)
	{
		current = current->next;
	}
	current->next = current->data + current->data_size;
	current->next->next = NULL;
	current->next->data = current->next + 1;
	current->next->is_busy = 1;
	current->next->data_size = size;
	current->next->is_new_page = 0;
	return (current->next);
}
