/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_ft_lstiter.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mprevot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/30 18:13:28 by mprevot           #+#    #+#             */
/*   Updated: 2016/11/30 18:15:01 by mprevot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

void    f1(t_list *elem)
{
	elem->content_size = 123;
}

int		main(void)
{
	// merci à dlouise
	t_list  elem1;
	t_list  elem2;
	t_list  elem3;
	t_list  elem4;

	elem1.next = &elem2;
	elem2.next = &elem3;
	elem3.next = &elem4;
	elem4.next = NULL;

	ft_lstiter(&elem1, f1);

	if (123 != elem1.content_size)
		return (10);
	if (123 != elem4.content_size)
		return (20);

	return (0);	
}
