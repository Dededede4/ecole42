/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heynard <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/28 17:45:30 by heynard           #+#    #+#             */
/*   Updated: 2016/11/29 14:15:47 by heynard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"

t_list		*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem))
{
	t_list	*tmp;
	t_list	*ret;

	if ((tmp = (t_list*)malloc(sizeof(t_list))) == NULL)
		return (NULL);
	tmp = f(lst);
	ret = tmp;
	while (lst->next != NULL)
	{
		if ((tmp->next = (t_list *)malloc(sizeof(t_list))) == NULL)
			return (NULL);
		lst = lst->next;
		tmp->next = f(lst);
		tmp = tmp->next;
	}
	return (ret);
}
