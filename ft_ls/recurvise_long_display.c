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

void recursive_long_display(t_path *pcur, t_file *file, t_params *param)
{
	t_path tmp_path;

	if (!file)
		return ;
	if (param->r)
		file = sort_lst_revert(file);
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
			recursive_long_display(&(tmp_path), findfiles(&(tmp_path)), param);
		}
		file = file->next;
	}
}
