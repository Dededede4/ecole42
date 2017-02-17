/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_intlst_issorted.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mprevot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/08 14:14:55 by mprevot           #+#    #+#             */
/*   Updated: 2017/02/08 14:14:57 by mprevot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_bool	ft_intlst_issorted(t_list *lst)
{
	int p;

	p = *((int*)lst->content);
	while (lst)
	{
		if (p > *((int*)lst->content))
			return (FALSE);
		p = *((int*)lst->content);
		lst = lst->next;
	}
	return (TRUE);
}
