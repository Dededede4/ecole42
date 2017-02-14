/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_freetvals.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mprevot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/10 16:59:31 by mprevot           #+#    #+#             */
/*   Updated: 2017/02/10 16:59:36 by mprevot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	ft_freecontent(void *content, size_t size)
{
	(void)size;
	if (content)
		free(content);
}

int		ft_freetvals(t_vals **vals)
{
	if (vals == NULL || *vals == NULL)
		return (1);
	ft_lstdel(vals, ft_freecontent);
	return (1);
}
