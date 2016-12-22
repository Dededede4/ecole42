/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_ft_lstadd.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mprevot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/30 14:51:58 by mprevot           #+#    #+#             */
/*   Updated: 2016/11/30 14:53:54 by mprevot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

int		main(void)
{
	// merci à dlouise
	t_list  *lst;
	t_list  *maillon;

	maillon = malloc(sizeof(t_list));
	lst = ft_lstnew("abc", 4);

	maillon->content_size = 5;
	maillon->content = malloc(5);
	strcpy((char*)maillon->content, "defg");
	ft_lstadd(&lst, maillon);

	if (0 != memcmp(lst->next->content, "abc", 4))
		return (10);

	if (4 != lst->next->content_size)
		return (20);

	if (5 != maillon->content_size)
		return (30);

	if (0 != memcmp(lst->content, "defg", 5))
		return (40);

	if (maillon != lst)
		return (50);

	return (0);
}
