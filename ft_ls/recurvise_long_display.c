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
		ft_memdel((void**)&(current->name));
		ft_memdel((void**)&(current->dir));
		ft_memdel((void**)&(current->path));
		ft_memdel((void**)&(current->path_link));
		ft_memdel((void**)&(current->error));
		ft_memdel((void**)&(current));
		current = next;
	}
}

void recursive_long_display_while(t_file *file, t_params *param)
{
	t_file	*f;
	t_path tmp_path;

	if (!file->name)
		return ;
	if (!param->a && file->name[0] == '.')
		return ;
	if (file->type == 'd' && ft_strcmp(file->name, ".") && ft_strcmp(file->name, ".."))
	{
		tmp_path.path = file->path;
		tmp_path.next = NULL;
		f = recursive_long_display(&(tmp_path), findfiles(&(tmp_path)), param);
		free_tfile(&f);
	}
}

t_file *recursive_long_display(t_path *pcur, t_file *file, t_params *param)
{
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
		recursive_long_display_while(file, param);
		file = file->next;
	}
	return first;
}
