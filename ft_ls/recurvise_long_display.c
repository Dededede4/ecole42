/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   recurvise_long_display.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mprevot <mprevot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/30 19:20:57 by mprevot           #+#    #+#             */
/*   Updated: 2015/01/30 19:55:49 by mprevot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	ft_memdelnull(void **ap)
{
	if (ap && *ap)
	{
		free(*ap);
		*ap = NULL;
	}
}


void free_tfile(t_file **file)
{
	t_file	*current;
	t_file	*next;

	if (!file || !*file)
		return ;
	current = *file;
	while (current)
	{
		next = current->next;
		//ft_memdelnull((void**)&(current->owner));
		//ft_memdelnull((void**)&(current->group));
		ft_memdel((void**)&(current->name));
		ft_memdel((void**)&(current->dir));
		ft_memdel((void**)&(current->path));
		ft_memdel((void**)&(current->path_link));
		ft_memdel((void**)&(current->error));
		ft_memdel((void**)&(current));
		current = next;
	}
	//ft_memdel((void**)file);
}

t_file *recursive_long_display(t_path *pcur, t_file *file, t_params *param)
{
	t_path tmp_path;
	t_file	*f;
	t_file	*first;

	if (!file)
		return NULL;
	if (param->t)
		file = sort_lst(file, tri_asc_time);
	if (param->r)
		file = sort_lst_revert(file);
	first = file;
	if (param->l)
		long_display(pcur, file, param);
	else
		sort_display(pcur, file, param);
	while (file)
	{
		if (!file->name)
		{
			file = file->next;
			continue;
		}
		if (!param->a && file->name[0] == '.')
		{
			file = file->next;
			continue;
		}
		if (file->type == 'd' && ft_strcmp(file->name, ".") && ft_strcmp(file->name, ".."))
		{
			tmp_path.path = file->path;
			tmp_path.next = NULL;
			f = recursive_long_display(&(tmp_path), findfiles(&(tmp_path)), param);
			free_tfile(&f);
		}
		file = file->next;
	}
	return first;
}
