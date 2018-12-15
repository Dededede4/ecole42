/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nm_tri.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mprevot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/15 03:22:18 by mprevot           #+#    #+#             */
/*   Updated: 2018/12/15 03:22:20 by mprevot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm.h"

void	tri_pourri_lol_switch(t_line *line, t_line *before, t_line **first)
{
	t_line	*tmp;

	if (before)
	{
		tmp = line->next->next;
		before->next = line->next;
		before->next->next = line;
		before->next->next->next = tmp;
	}
	else
	{
		tmp = line->next->next;
		*first = line->next;
		(*first)->next = line;
		(*first)->next->next = tmp;
	}
}

void	tri_pourri_lol(t_line **first)
{
	t_line	*line;
	t_line	*before;
	int		diff;

	line = *first;
	before = NULL;
	while (line->next)
	{
		diff = ft_strcmp(line->right, line->next->right);
		if (diff > 0 ||
			(diff == 0 && line->left > 0 && line->next->left == 0) ||
			(diff == 0 && line->left != 0 && line->next->left != 0 &&
			line->left > line->next->left))
		{
			tri_pourri_lol_switch(line, before, first);
			line = *first;
			before = NULL;
			continue;
		}
		before = line;
		line = line->next;
	}
}
