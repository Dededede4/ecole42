/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_files.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mprevot <mprevot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/12/05 15:53:18 by mprevot           #+#    #+#             */
/*   Updated: 2014/12/05 16:55:32 by mprevot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"
#include <errno.h>

int		isdirectory(const char *path)
{
	struct stat statbuf;

	if (stat(path, &statbuf) != 0)
		return (0);
	return (S_ISDIR(statbuf.st_mode));
}

t_file	*findfiles_dir_while(t_path *path, struct dirent *dirent)
{
	t_file	*file;

	file = ft_memalloc(sizeof(*file));
	file->error = NULL;
	file->dir = find_folder_by_path(path->path);
	file->name = ft_strdup(dirent->d_name);
	file->path = ft_strjoin_multi(TRUE,
		ft_strdup(file->dir), ft_strjoin("/", file->name), NULL);
	set_right(file);
	file->next = NULL;
	return (file);
}

t_file	*findfiles_dir(t_path *path)
{
	t_file			*file;
	t_file			*file_tmp;
	DIR				*dir;
	struct dirent	*dirent;

	file_tmp = NULL;
	if (!(dir = opendir(path->path)))
	{
		file = ft_memalloc(sizeof(*file));
		file->dir = ft_strdup(path->path);
		file->type = 'd';
		file->error = ft_strjoin_multi(FALSE, "ls: ",
			find_name_by_path(path->path), ": ", strerror(errno), "\n", NULL);
		return (file);
	}
	while ((dirent = readdir(dir)))
	{
		file = findfiles_dir_while(path, dirent);
		if (!file_tmp)
			file_tmp = file;
		else
			lst_file_add_end(file_tmp, file);
	}
	closedir(dir);
	return (file_tmp);
}

t_file	*findfiles_nodir(t_path *path)
{
	t_file			*file;

	file = ft_memalloc(sizeof(*file));
	file->error = NULL;
	file->dir = find_folder_by_path(path->path);
	file->name = ft_strdup(find_name_by_path(path->path));
	file->path = ft_strjoin(file->dir, ft_strjoin("/", file->name));
	set_right(file);
	file->next = NULL;
	return (file);
}

t_file	*findfiles(t_path *path)
{
	return ((isdirectory(path->path)) ?
		findfiles_dir(path) : findfiles_nodir(path));
}
