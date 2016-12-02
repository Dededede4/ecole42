/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mprevot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/30 18:22:38 by mprevot           #+#    #+#             */
/*   Updated: 2016/12/02 16:19:39 by mprevot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	ft_ondelete(void *content, size_t len)
{
	(void)len;
	free(content);
	content = NULL;
}

t_list		*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem))
{
	t_list	*next;
	t_list	*new_first;
	t_list	*new_current;

	if (lst == NULL)
		return (NULL);
	new_first = f(lst);
	if (new_first == NULL)
		return (NULL);
	new_current = new_first;
	while (lst->next)
	{
		next = lst->next;
		new_current->next = f(next);
		if (new_current->next == NULL)
		{
			ft_lstdel(&new_first, ft_ondelete);
			return (NULL);
		}
		lst = next;
		new_current = new_current->next;
	}
	return (new_first);
}
