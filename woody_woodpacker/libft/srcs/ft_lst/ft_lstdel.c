/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdel.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heynard <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/28 17:08:33 by heynard           #+#    #+#             */
/*   Updated: 2016/11/28 17:31:41 by heynard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"

void		ft_lstdel(t_list **alst, void (*del)(void *, size_t))
{
	t_list	*tmp;
	t_list	*tmp_next;

	tmp = *alst;
	while (tmp)
	{
		tmp_next = tmp->next;
		del(tmp->content, tmp->content_size);
		free(tmp);
		tmp = tmp_next;
	}
	*alst = NULL;
}
