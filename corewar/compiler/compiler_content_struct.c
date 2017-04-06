/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   compiler_content_struct.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mprevot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/23 21:00:58 by mprevot           #+#    #+#             */
/*   Updated: 2017/03/23 21:00:59 by mprevot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "compiler.h"

void			instructs_add(t_instruct **instructs_list, t_instruct *instruct)
{
	t_instruct	*current;

	current = *instructs_list;
	if (!current)
	{
		*instructs_list = instruct;
		return ;
	}
	while (current->next)
		current = current->next;
	current->next = instruct;
}

size_t			get_instruct_size(t_instruct *current)
{
	size_t		size;

	size = 0;
	while (current)
	{
		size += current->size;
		current = current->next;
	}
	return (size);
}
