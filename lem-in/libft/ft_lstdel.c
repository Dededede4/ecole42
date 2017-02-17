/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdel.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mprevot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/30 13:56:53 by mprevot           #+#    #+#             */
/*   Updated: 2016/11/30 14:41:52 by mprevot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstdel(t_list **alst, void (*del)(void*, size_t))
{
	t_list	*lst;
	t_list	*next;

	lst = *alst;
	next = lst;
	while (lst)
	{
		next = lst->next;
		lst->next = NULL;
		ft_lstdelone(&lst, del);
		lst = next;
	}
	*alst = NULL;
}
