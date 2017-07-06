/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tab_to_lst.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mprevot <mprevot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/12/03 13:32:29 by mprevot           #+#    #+#             */
/*   Updated: 2014/12/05 11:15:17 by mprevot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	tab_to_lst(t_file **data, size_t len)
{
	size_t i;

	i = 0;
	data[len - 1]->next = NULL;
	while (i < len)
	{
		data[i]->next = data[i + 1];
		i++;
	}
}


void	tab_to_lst_path(t_path **data, size_t len)
{
	size_t i;

	i = 0;
	data[len - 1]->next = NULL;
	while (i < len)
	{
		data[i]->next = data[i + 1];
		i++;
	}
}
