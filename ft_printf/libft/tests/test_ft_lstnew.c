/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_ft_lstnew.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mprevot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/30 10:17:39 by mprevot           #+#    #+#             */
/*   Updated: 2016/11/30 10:53:32 by mprevot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

int		main(void)
{
	t_list	*new = ft_lstnew("ABC", 4);
	if (strcmp(new->content, "ABC") != 0)
		return (10);
	if (new->content_size != 4)
		return (20);
	if (new->next != NULL)
		return (30);

	new = ft_lstnew(NULL, 42);
	if (new->content != NULL)
		return (40);
	if (new->content_size != 0)
		return (50);
	if (new->next != NULL)
		return (60);
}
