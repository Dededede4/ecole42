/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memalloc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mprevot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/28 10:19:11 by mprevot           #+#    #+#             */
/*   Updated: 2017/03/28 13:16:09 by mprevot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnew2(void const *content, size_t content_size)
{
	t_list	*new;

	if (!new = malloc(sizeof(t_list)))
		exit(0);
	if (content_size)
	{
		if(!new->content = malloc(content_size))
			exit(0);
		new->content_size = content_size;
		ft_memcpy(new->content, content, content_size);
	}
	else
	{
		new->content = NULL;
		new->content_size = 0;
	}
	new->next = NULL;
	return (new);
}

void	storeptr(void *ptr)
{
	static t_list *list = NULL;

	if (!list)
	{
		list = ft_lstnew2(&ptr, 8);
	}
	else
	{
		ft_lstadd(&list, ft_lstnew2(&ptr, 8));
	}
}

void	*ft_memalloc(size_t size)
{
	void	*mem;

	mem = malloc(size);
	if (!mem)
		exit(0);
	if (!DEBUG)
		storeptr(mem);
	ft_bzero(mem, size);
	return (mem);
}
