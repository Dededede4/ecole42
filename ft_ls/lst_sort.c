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

int		tri_asc_size(void *f1, void *f2)
{
	return (((t_file *)f1)->bytes - ((t_file *)f2)->bytes);
}

int		tri_asc_time(void *f1, void *f2)
{
	return (((t_file *)f1)->modified.tv_sec < ((t_file *)f2)->modified.tv_sec);
}

int		tri_asc_ascii(void *f1, void *f2)
{
	return (ft_strcmp(((t_file *)f1)->name, ((t_file *)f2)->name));
}

t_file *sort_lst(t_file *f, int (*func)(void*, void*))
{
	size_t	len;
	void	**data;
	void	**first;
	t_file	*r;

	len = 0;
	data = (void **)lst_to_tab(f, &len);
	first = data;
	bubblesort(data, func, len);
	tab_to_lst((t_file **)data, len);
	r = data[0];
	ft_memdel((void**)&first);
	return r;
}


time_t	get_time(char *path)
{
	struct stat		fstat;
	time_t null;

	if (lstat(path, &fstat) >= 0)
		return fstat.st_mtimespec.tv_sec;
	ft_err("error\n");
	return (null);
}

int	get_bytes(char *path)
{
	struct stat		fstat;
	if (lstat(path, &fstat) >= 0)
		return fstat.st_size;
	ft_err("error\n");
	return (0);
}

int		tri_asc_size_path(void *f1, void *f2)
{
	return (get_bytes((((t_path *)f1)->path)) - get_bytes(((t_path *)f2)->path));
}

int		tri_asc_time_path(void *f1, void *f2)
{
	return ((get_time(((t_path *)f1)->path))  < get_time(((t_path *)f2)->path));
}


int		tri_asc_ascii_path(void *f1, void *f2)
{
	return (ft_strcmp(((t_path *)f1)->path, ((t_path *)f2)->path));
}

t_path *sort_lst_path(t_path *f, int (*func)(void*, void*))
{
	size_t	len;
	void	**data;
	void	**first;
	t_path *r;

	len = 0;
	data = (void **)lst_to_tab_path(f, &len);
	first = data;
	bubblesort(data, func, len);
	tab_to_lst_path((t_path **)data, len);
	r = data[0];
	ft_memdel((void **)&first);
	return r;
}


t_file 	*sort_lst_revert(t_file *f)
{
	t_file	*current;
	t_file	*previous;
	t_file	*next;

	current = f;
	previous = current;
	next = current->next;
	current->next = NULL;
	while (next)
	{
		current = next;
		next = current->next;
		current->next = previous;
		previous = current;
	}
	return (previous);
}


t_path 	*sort_lst_revert_path(t_path *f)
{
	t_path	*current;
	t_path	*previous;
	t_path	*next;

	current = f;
	previous = current;
	next = current->next;
	current->next = NULL;
	while (next)
	{
		current = next;
		next = current->next;
		current->next = previous;
		previous = current;
	}
	return (previous);
}