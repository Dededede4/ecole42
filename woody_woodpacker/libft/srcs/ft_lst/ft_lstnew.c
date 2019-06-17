/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heynard <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/28 16:39:41 by heynard           #+#    #+#             */
/*   Updated: 2016/11/28 16:56:30 by heynard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"

t_list		*ft_lstnew(void const *content, size_t content_size)
{
	t_list	*link_new;

	if ((link_new = malloc(sizeof(t_list))) == NULL)
		return (NULL);
	if (content == NULL)
	{
		link_new->content = NULL;
		link_new->content_size = 0;
	}
	else
	{
		link_new->content = (void *)content;
		link_new->content_size = content_size;
	}
	link_new->next = NULL;
	return (link_new);
}
