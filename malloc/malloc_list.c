/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc_list.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mprevot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/08 21:11:16 by mprevot           #+#    #+#             */
/*   Updated: 2018/09/08 21:11:20 by mprevot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

static void		*create_zone_from_mem(t_list *page)
{
	t_list *l;

	l = page->next;
	page->next = page->data + page->data_size;
	page->next->next = l;
	page->next->data = page->next + 1;
	page->next->is_busy = 1;
	page->next->data_size = size;
	page->next->is_new_page = 0;
	return (page->next->data);
}

static void		*malloc_list_after(size_t size, t_list **page_container,
	size_t page_used_size)
{
	if ((getpagesize() - page_used_size) > (sizeof(t_list) + size) &&
		pd("\x1B[31m-> Une zone dans la dernière page\x1B[0m\n"))
		return ((malloc_nopage_list(size, page_container))->data);
	pd("\x1B[31m-> Une nouvelle page car il n'y a plus de place\x1B[0m\n");
	return ((malloc_page_list(size, page_container))->data);
}

static void		*malloc_list(size_t size, t_list **page_container)
{
	size_t page_used_size;
	t_list *page;

	page = *page_container;
	if (NULL == *page_container && !(page_used_size = 0) &&
		pd("\x1B[31m-> Nouvelle page car c'est le premier\x1B[0m\n"))
		return ((malloc_page_list(size, page_container))->data);
	while (page)
	{
		if (page->is_busy == 0 && page->data_size >= size && (page->is_busy = 1)
			&& pd("\x1B[31m-> Donne le malloc à un bloc de ")
			&& ft_putnbr_fd_debug(page->data_size, 1) && pd(" octets\x1B[0m\n"))
			return (page->data);
		page_used_size += page->data_size + sizeof(t_list);
		if (page->next && page->next->is_new_page)
			if ((getpagesize() - page_used_size) > (sizeof(t_list) + size) &&
				pd("\x1B[31m-> Une zone dans une page d'avant\x1B[0m\n"))
				return (create_zone_from_mem(page));
			else
				page_used_size = 0;
		page = page->next;
	}
	return (malloc_list_after(size, page_container, page_used_size));
}
