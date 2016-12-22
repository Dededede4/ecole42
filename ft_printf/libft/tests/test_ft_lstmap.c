/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_ft_lstmap.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mprevot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/30 18:32:50 by mprevot           #+#    #+#             */
/*   Updated: 2016/11/30 18:34:56 by mprevot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

t_list    *f2(t_list *elem)
{
	t_list  *new;

	new = malloc(sizeof(t_list));
	new->content_size = elem->content_size + 10;
	new->content = malloc(elem->content_size + 10);

	return (new);
}

int		main(void)
{
	// merci à dlouise
	t_list  elem1;
	t_list  elem2;
	t_list  elem3;
	t_list  elem4;
	t_list  *result;

	elem1.next = &elem2;
	elem2.next = &elem3;
	elem3.next = &elem4;
	elem4.next = NULL;


	elem1.content_size = 5;
	elem2.content_size = 6;
	elem3.content_size = 7;
	elem4.content_size = 8;

	elem1.content = malloc(5);
	elem2.content = malloc(6);
	elem3.content = malloc(7);
	elem4.content = malloc(8);

	result = ft_lstmap(&elem1, f2);

	if (15 != result->content_size)
		return (10);
	if (16 != result->next->content_size)
		return (20);
	if (17 != result->next->next->content_size)
		return (30);
	if (18 != result->next->next->next->content_size)
		return (40);

	return (0);
}
