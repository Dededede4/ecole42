/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_to_tab.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mprevot <mprevot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/12/03 13:31:14 by mprevot           #+#    #+#             */
/*   Updated: 2014/12/05 10:48:18 by mprevot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

t_file **lst_to_tab(t_file *file, size_t *i)
{
	t_file	**tab;
	size_t	j;

	*i = lst_len(file);
	j = 0;
	if (!(tab = ft_memalloc(sizeof(**tab) * (*i + 1))))
		return (NULL);
	while (j < *i)
	{
		tab[j++] = file;
		file = file->next;
	}
	tab[j] = NULL;
	return (tab);
}


t_path **lst_to_tab_path(t_path *file, size_t *i)
{
	t_path	**tab;
	size_t	j;

	*i = lst_len_path(file);
	j = 0;
	if (!(tab = ft_memalloc(sizeof(**tab) * (*i + 1))))
		return (NULL);
	while (j < *i)
	{
		tab[j++] = file;
		file = file->next;
	}
	tab[j] = NULL;
	return (tab);
}
