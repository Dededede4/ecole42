/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_revert.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mprevot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/17 21:14:48 by mprevot           #+#    #+#             */
/*   Updated: 2017/07/17 21:14:50 by mprevot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

t_file	*sort_lst_revert(t_file *f)
{
	t_file	*current;
	t_file	*previous;
	t_file	*next;

	current = f;
	previous = current;
	next = current->next;
	current->next = NULL;
	while (next)
	{
		current = next;
		next = current->next;
		current->next = previous;
		previous = current;
	}
	return (previous);
}

t_path	*sort_lst_revert_path(t_path *f)
{
	t_path	*current;
	t_path	*previous;
	t_path	*next;

	current = f;
	previous = current;
	next = current->next;
	current->next = NULL;
	while (next)
	{
		current = next;
		next = current->next;
		current->next = previous;
		previous = current;
	}
	return (previous);
}
