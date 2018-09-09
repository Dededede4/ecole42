/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc_page_large.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mprevot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/08 22:26:09 by mprevot           #+#    #+#             */
/*   Updated: 2018/09/08 22:26:21 by mprevot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

t_list	*malloc_page_large(size_t size)
{
	t_list		*current;

	if (g_container.large)
	{
		current = g_container.large;
		while (current->next)
		{
			current = current->next;
		}
		current->next = malloc_direct(size);
		return (current->next);
	}
	else
	{
		g_container.large = malloc_direct(size);
		return (g_container.large);
	}
}
