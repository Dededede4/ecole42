/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_sort.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mprevot <mprevot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/12/03 14:13:32 by mprevot           #+#    #+#             */
/*   Updated: 2014/12/05 10:51:00 by mprevot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

t_file	*sort_lst(t_file *f, int (*func)(void*, void*))
{
	size_t			len;
	void			**data;
	void			**first;
	t_file			*r;

	len = 0;
	data = (void **)lst_to_tab(f, &len);
	first = data;
	bubblesort(data, func, len);
	tab_to_lst((t_file **)data, len);
	r = data[0];
	ft_memdel((void**)&first);
	return (r);
}

time_t	get_time(char *path)
{
	struct stat		fstat;
	time_t			null;

	if (lstat(path, &fstat) >= 0)
		return (fstat.st_mtimespec.tv_sec);
	ft_err("error\n");
	return (null);
}

int		get_bytes(char *path)
{
	struct stat		fstat;

	if (lstat(path, &fstat) >= 0)
		return (fstat.st_size);
	ft_err("error\n");
	return (0);
}

t_path	*sort_lst_path(t_path *f, int (*func)(void*, void*))
{
	size_t			len;
	void			**data;
	void			**first;
	t_path			*r;

	len = 0;
	data = (void **)lst_to_tab_path(f, &len);
	first = data;
	bubblesort(data, func, len);
	tab_to_lst_path((t_path **)data, len);
	r = data[0];
	ft_memdel((void **)&first);
	return (r);
}
