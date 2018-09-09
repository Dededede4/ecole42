/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mprevot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/08 20:17:58 by mprevot           #+#    #+#             */
/*   Updated: 2018/09/08 20:18:00 by mprevot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

t_all g_container;

void	ft_free_large(void *addr)
{
	t_list		*current;
	t_list		*before;
	size_t		size_alloc;

	current = g_container.large;
	before = NULL;
	while (current)
	{
		if (current->data == addr)
		{
			if (DEBUG_MALLOC)
				ft_putnbr_fd(current->data_size, 1);
			size_alloc = current->data_size + sizeof(t_list);
			size_alloc = ((size_alloc / getpagesize()) + 1) * getpagesize();
			if (NULL == before)
			{
				g_container.large = current->next;
				munmap(current, size_alloc);
				return ;
			}
			before->next = current->next;
			munmap(current, size_alloc);
			return ;
		}
		before = current;
		current = current->next;
	}
}

void	ft_free_container_checkmunmap_nobusyfind(
	t_list **page_container, t_list *before_page_start,
	t_list *current, t_list *page_start)
{
	return ;
	if (before_page_start == NULL)
		*page_container = (current->next == NULL) ? NULL : current;
	else
		before_page_start->next = current;
	if (DEBUG_MALLOC)
		ft_putstr(" (munmap)");
	munmap(page_start, getpagesize());
}

/*
** Petit algo pour parcourir les élèments de la liste,
** si entre deux pages tout est vide, on peut le munmap.
*/

void	ft_free_container_checkmunmap(t_list **page_container)
{
	t_list		*page_start;
	t_list		*before_page_start;
	t_list		*old_current;
	bool		busy_find;
	t_list		*current;

	page_start = *page_container;
	before_page_start = NULL;
	current = page_start;
	busy_find = false;
	while (current)
	{
		if (current != *page_container &&
			(current->is_new_page || current->next == NULL))
		{
			if (!busy_find)
				return (ft_free_container_checkmunmap_nobusyfind(
					page_container, before_page_start, current, page_start));
				page_start = current;
		}
		if (current->is_busy)
			busy_find = true;
		old_current = current;
		current = current->next;
	}
}

void	ft_free_container(void *addr, t_list **page_container)
{
	t_list	*current;

	if (!(current = find_item_list(addr, page_container)))
		return ;
	if (current->is_busy == 0)
		return ;
	if (DEBUG_MALLOC)
		ft_putnbr_fd(current->data_size, 1);
	current->is_busy = 0;
	ft_free_container_checkmunmap(page_container);
}

void	ft_free(void *addr)
{
	if (DEBUG_MALLOC)
		write(1, "\x1B[31mfree(", 11);
	ft_free_large(addr);
	ft_free_container(addr, &g_container.tiny);
	ft_free_container(addr, &g_container.small);
	pd(");\x1B[0m\n");
}
