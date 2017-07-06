/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mprevot <mprevot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/12/03 13:49:08 by mprevot           #+#    #+#             */
/*   Updated: 2014/12/05 15:55:51 by mprevot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void bubblesort(void **data, int (*f)(void *, void *), size_t len)
{
	size_t	i;
	void	*tmp;

	i = 0;
	while (i + 1 < len)
	{
		if (f(data[i], data[i + 1]) > 0)
		{
			tmp = data[i];
			data[i] = data[i + 1];
			data[i + 1] = tmp;
			i = 0;
		}
		else
			i++;
	}
}
