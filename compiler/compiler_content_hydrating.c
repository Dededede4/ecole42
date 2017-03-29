/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   compiler_content_hydrating.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mprevot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/23 21:01:12 by mprevot           #+#    #+#             */
/*   Updated: 2017/03/23 21:01:14 by mprevot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "compiler.h"

size_t			get_label_position(t_instruct *first, char *labelname)
{
	t_instruct	*current;
	int			count;
	t_bool		finded;

	current = first;
	finded = FALSE;
	count = 0;
	while (current)
	{
		if (ft_strcmp(current->label_name, labelname) == 0)
		{
			finded = TRUE;
			break ;
		}
		count += current->size;
		current = current->next;
	}
	if (!finded)
		error("Label not exist\n");
	return (count);
}

size_t			get_request_label_position(
	t_instruct *first, t_instruct *tofind)
{
	t_instruct	*current;
	int			count;
	t_bool		finded;

	current = first;
	finded = FALSE;
	count = 0;
	while (current)
	{
		if (current == tofind)
		{
			finded = TRUE;
			break ;
		}
		count += current->size;
		current = current->next;
	}
	if (!finded)
		error("Unknow error\n");
	return (count);
}

size_t			get_relative(
	t_instruct *first, t_instruct *tofind, char *labelname)
{
	return (get_label_position(first, labelname) -
		get_request_label_position(first, tofind));
}

void			hydrate_labels(t_instruct *first)
{
	t_instruct	*current;
	int			pos;
	int			i;

	current = first;
	while (current)
	{
		i = 0;
		while (i < 3)
		{
			if (current->args_labels[i])
			{
				pos = get_relative(first, current, current->args_labels[i]);
				ft_memmove(current->args[i] + 2, &pos, current->args[i][1]);
			}
			i++;
		}
		current = current->next;
	}
}
