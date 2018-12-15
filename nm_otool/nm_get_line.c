/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nm_get_line.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mprevot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/15 03:19:55 by mprevot           #+#    #+#             */
/*   Updated: 2018/12/15 03:20:02 by mprevot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm.h"

t_line	*get_line(int nsyms, int symoff, int stroff, char *ptr)
{
	int				i;
	char			*stringtable;
	struct nlist_64	*el;
	t_line			*line;
	t_line			*tmp;

	line = NULL;
	tmp = NULL;
	el = (void*)ptr + symoff;
	stringtable = ptr + stroff;
	i = 0;
	while (i < nsyms)
	{
		tmp = ft_memalloc(sizeof(*line));
		if (line)
			tmp->next = line;
		line = tmp;
		line->left = el[i].n_value;
		line->middle = get_type(el[i]);
		line->right = stringtable + el[i].n_un.n_strx;
		line->is_64 = TRUE;
		line->is_32 = FALSE;
		i++;
	}
	return (line);
}

t_line	*get_line_32(int nsyms, int symoff, int stroff, void *ptr)
{
	int				i;
	char			*stringtable;
	struct nlist	*el;
	t_line			*line;
	t_line			*tmp;

	line = NULL;
	tmp = NULL;
	el = (void*)ptr + symoff;
	stringtable = ptr + stroff;
	i = 0;
	while (i < nsyms)
	{
		tmp = ft_memalloc(sizeof(*line));
		if (line)
			tmp->next = line;
		line = tmp;
		line->left = el[i].n_value;
		line->middle = get_type_32(el[i]);
		line->right = stringtable + el[i].n_un.n_strx;
		line->is_32 = TRUE;
		line->is_64 = FALSE;
		i++;
	}
	return (line);
}
