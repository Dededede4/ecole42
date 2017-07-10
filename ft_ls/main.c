/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mprevot <mprevot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/25 17:26:43 by mprevot           #+#    #+#             */
/*   Updated: 2015/01/30 19:40:47 by mprevot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"
// Pour errno
#include <errno.h>

#include <stdio.h> // pd

int main(int argc, char **argv)
{
	t_params	*params;
	t_file		*file;
	t_path		*current;
	t_bool		s;

	errno = 0;
	params = extractParams(argc, argv);

	params->paths = sort_lst_path(params->paths, tri_asc_ascii_path);
	if (params->t)
		params->paths = sort_lst_path(params->paths, tri_asc_time_path);
	if (params->r && params->paths)
		params->paths = sort_lst_revert_path(params->paths);

	// Les fichiers avant puis les directory
	s = FALSE;
	current = params->paths;
	while (current)
	{
		if (isDirectory(current->path))
		{
			current = current->next;
			continue;
		}
		if (!(file = findfiles(current)))
		{
			current = current->next;
			continue;
		}
		s = TRUE;
		file = sort_lst(file, tri_asc_ascii);
		if (params->t)
			file = sort_lst(file, tri_asc_time);
		if (params->r)
			file = sort_lst_revert(file);
		if (params->R && !params->R)
			recursive_long_display(current, file, params);
		else
		{
			if (params->l)
				long_display(current, file, params);
			else
				sort_display(current, file, params);
		}
		current = current->next;
	}
	if (s)
		ft_putchar('\n');
	current = params->paths;
	while (current)
	{
		if (!isDirectory(current->path))
		{
			current = current->next;
			continue;
		}
		if (!(file = findfiles(current)))
		{
			current = current->next;
			continue;
		}
		file = sort_lst(file, tri_asc_ascii);
		if (params->t)
			file = sort_lst(file, tri_asc_time);
		if (params->r && !params->R)
			file = sort_lst_revert(file);
		if (params->R)
			recursive_long_display(current, file, params);
		else
		{
			if (params->l)
				long_display(current, file, params);
			else
				sort_display(current, file, params);
		}
		current = current->next;
	}
	return (0);
}
