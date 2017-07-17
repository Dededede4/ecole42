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
#include <errno.h>

int		main_onwhile(t_bool after, t_path *current, t_params *params)
{
	t_file		*file;

	if ((after && !isdirectory(current->path)) ||
		(!after && isdirectory(current->path)))
		return (1);
	if (!(file = findfiles(current)))
		return (0);
	file = sort_lst(file, tri_asc_ascii);
	if (params->t)
		file = sort_lst(file, tri_asc_time);
	if (params->r && !params->rr)
		file = sort_lst_revert(file);
	if (params->rr && after)
		recursive_long_display(current, file, params);
	else
	{
		if (params->l)
			long_display(current, file, params);
		else
			sort_display(current, file, params);
	}
	return (0);
}

void	main_print(t_params *params)
{
	t_path		*current;
	int			leneff;
	int			len;

	current = params->paths;
	leneff = 0;
	len = 0;
	while (current)
	{
		leneff += main_onwhile(FALSE, current, params);
		len++;
		current = current->next;
	}
	if (len > leneff && leneff)
		ft_putchar('\n');
	current = params->paths;
	while (current)
	{
		main_onwhile(TRUE, current, params);
		current = current->next;
	}
}

int		main(int argc, char **argv)
{
	t_params	*params;

	errno = 0;
	params = extractparams(argc, argv);
	params->paths = sort_lst_path(params->paths, tri_asc_ascii_path);
	if (params->t)
		params->paths = sort_lst_path(params->paths, tri_asc_time_path);
	if (params->r && params->paths)
		params->paths = sort_lst_revert_path(params->paths);
	main_print(params);
	exit(0);
}
