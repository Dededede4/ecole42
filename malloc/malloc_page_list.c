/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc_page_list.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mprevot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/08 22:25:28 by mprevot           #+#    #+#             */
/*   Updated: 2018/09/08 22:25:39 by mprevot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

t_list	*malloc_page_list(size_t size, t_list **page_container)
{
	t_list *current;

	if (*page_container)
	{
		current = *page_container;
		while (current->next)
		{
			current = current->next;
		}
		current->next = malloc_direct(size);
		return (current->next);
	}
	else
	{
		*page_container = malloc_direct(size);
		return (*page_container);
	}
}

