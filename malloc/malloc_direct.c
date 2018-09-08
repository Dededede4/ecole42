/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc_direct.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mprevot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/08 22:24:49 by mprevot           #+#    #+#             */
/*   Updated: 2018/09/08 22:25:10 by mprevot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

tatic t_list	*malloc_direct(size_t size)
{
	size_t	size_alloc;
	t_list	*l;

	size_alloc = size + sizeof(t_list);
	size_alloc = ((size_alloc / getpagesize()) + 1) * getpagesize();
	l = mmap(NULL, size_alloc, PROT_READ | PROT_WRITE, MAP_ANON|MAP_PRIVATE, -1, 0);
	l->data_size = size;
	l->data = l + 1;
	l->is_busy = 1;
	l->is_new_page = 1;
	l->next = NULL;
	return (l);
}
