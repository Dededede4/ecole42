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
char	type_to_char(mode_t c)
{
	if ((c & S_IFMT) == S_IFIFO)
		return ('p');
	if ((c & S_IFMT) == S_IFCHR)
		return ('c');
	if ((c & S_IFMT) == S_IFDIR)
		return ('d');
	if ((c & S_IFMT) == S_IFBLK)
		return ('b');
	if ((c & S_IFMT) == S_IFREG)
		return ('-');
	if ((c & S_IFMT) == S_IFLNK)
		return ('l');
	if ((c & S_IFMT) == S_IFSOCK)
		return ('s');
	return ('?');
}

void	get_right(t_file *file, struct stat fstat)
{
	file->right[0] = (fstat.st_mode & S_IRUSR) ? 'r' : '-';
	file->right[1] = (fstat.st_mode & S_IWUSR) ? 'w' : '-';
	file->right[2] = (fstat.st_mode & S_IXUSR) ? 'x' : '-';
	file->right[3] = (fstat.st_mode & S_IRGRP) ? 'r' : '-';
	file->right[4] = (fstat.st_mode & S_IWGRP) ? 'w' : '-';
	file->right[5] = (fstat.st_mode & S_IXGRP) ? 'x' : '-';
	file->right[6] = (fstat.st_mode & S_IROTH) ? 'r' : '-';
	file->right[7] = (fstat.st_mode & S_IWOTH) ? 'w' : '-';
	file->right[8] = (fstat.st_mode & S_IXOTH) ? 'x' : '-';
	file->right[9] = 0;
}

char *find_name_by_path(char *path)
{
	char *find;

	if ((find = ft_strrchr(path, '/')))
		return find + 1;
	return path;
}

void	set_right(t_file *file)
{
	struct stat		fstat;
	struct passwd	*pw;
	struct group	*gr;

	if (lstat(file->path, &fstat) >= 0)
	{
		file->type = type_to_char(fstat.st_mode);
		file->bytes = fstat.st_size;
		file->links = fstat.st_nlink;
		get_right(file, fstat);
		file->lstacess = fstat.st_atimespec;
		file->modified = fstat.st_mtimespec;
		file->mtime = fstat.st_mtime;
		file->lststatchg = fstat.st_ctimespec;
		file->blocks = fstat.st_blocks;
		if ((pw = getpwuid(fstat.st_uid)))
			file->owner = pw->pw_name;
		if ((gr = getgrgid(fstat.st_gid)))
			file->group = gr->gr_name;
		file->major = (file->type == 'c' || file->type == 'b') ? major(fstat.st_rdev) : 0;
		file->minor = (file->type == 'c' || file->type == 'b') ? minor(fstat.st_rdev) : 0;
	}
	else
		ft_err(ft_strjoin_multi(FALSE, "ls: ", find_name_by_path(file->path), ": No such file or directory\n", NULL));
}



char *find_folder_by_path(char *path)
{
	char *find;

	if (ft_strchr(path, '/'))
		return ft_strdup(path);
	if (isDirectory(path))
		return ft_strdup(path);
	return ft_strdup(".");
}

int isDirectory(const char *path) {
   struct stat statbuf;
   if (stat(path, &statbuf) != 0)
       return 0;
   return S_ISDIR(statbuf.st_mode);
}

t_file *findfiles_dir_while(t_path *path, struct dirent *dirent)
{
	t_file	*file;

	file = ft_memalloc(sizeof(*file));
	file->error = NULL;
	file->dir = find_folder_by_path(path->path);
	file->name = ft_strdup(dirent->d_name);
	file->path = ft_strjoin_multi(TRUE, ft_strdup(file->dir), ft_strjoin("/", file->name), NULL);
	set_right(file);
	file->next = NULL;
	return (file);
}

t_file *findfiles_dir(t_path *path)
{
	t_file			*file;
	t_file			*file_tmp;
	DIR				*dir;
	struct dirent	*dirent;

	file_tmp = NULL;
	if (!(dir = opendir(path->path)))
	{
		file = ft_memalloc(sizeof(*file));
		file->next = NULL;
		file->dir = ft_strdup(path->path);
		file->type = 'd';
		file->error = ft_strjoin_multi(FALSE, "ls: ", find_name_by_path(path->path), ": ", strerror(errno), "\n", NULL);
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

t_file *findfiles_nodir(t_path *path)
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

t_file *findfiles(t_path *path)
{
	return ((isDirectory(path->path)) ? findfiles_dir(path) : findfiles_nodir(path));
}
