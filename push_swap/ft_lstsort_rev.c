/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsort_rev.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mprevot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/08 16:34:27 by mprevot           #+#    #+#             */
/*   Updated: 2017/02/08 16:34:29 by mprevot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

t_list		*ft_lstsort_add_rev(t_list **lst, t_list *one)
{
	t_list	*current;
	t_list	*next;

	next = one->next;
	one->next = NULL;
	if (*lst == NULL)
	{
		*lst = one;
		return (next);
	}
	current = *lst;
	while (current->next)
		current = current->next;
	current->next = one;
	return (next);
}

void		ft_lstsort_merge_rev(t_list **lst, size_t dup, size_t len)
{
	t_list	*lst1;
	t_list	*lst2;
	size_t	i;

	i = 0;
	if (dup >= len)
		return ;
	while (i + dup < len)
	{
		lst1 = lst[i];
		lst2 = lst[i + dup];
		lst[i] = NULL;
		lst[i + dup] = NULL;
		while (lst1 || lst2)
			if (lst1 && !lst2)
				lst1 = ft_lstsort_add_rev(lst + i, lst1);
			else if (!lst1 && lst2)
				lst2 = ft_lstsort_add_rev(lst + i, lst2);
			else if (*((int*)lst1->content) >= *((int*)lst2->content))
				lst1 = ft_lstsort_add_rev(lst + i, lst1);
			else if (*((int*)lst1->content) <= *((int*)lst2->content))
				lst2 = ft_lstsort_add_rev(lst + i, lst2);
		i += dup * 2;
	}
	ft_lstsort_merge_rev(lst, dup * 2, len);
}

t_list		*ft_lstsort_rev(t_list *lst)
{
	t_list	**stacks;
	t_list	*r;
	size_t	i;

	stacks = ft_memalloc((ft_lstlen(lst) + 1) * sizeof(void*));
	i = 0;
	while (lst)
	{
		stacks[i] = ft_lstnew(lst->content, lst->content_size);
		lst = lst->next;
		i++;
	}
	ft_lstsort_merge_rev(stacks, 1, i);
	r = stacks[0];
	free(stacks);
	return (r);
}
