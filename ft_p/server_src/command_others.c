/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_others.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mprevot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/08 19:10:43 by mprevot           #+#    #+#             */
/*   Updated: 2019/03/08 19:10:44 by mprevot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"

/*
** REV(\n 57 344 \n)
*/

void	show_ls(int fd, char *path)
{
	DIR				*d;
	struct dirent	*dir;
	int				stop;

	stop = 0x0A00E00A;
	d = opendir(path);
	if (d)
	{
		while ((dir = readdir(d)) != NULL)
		{
			ft_printf("-->%s<--\n", dir->d_name);
			ft_putstr_fd(dir->d_name, fd);
			ft_putstr_fd(" ; ", fd);
		}
		closedir(d);
	}
	else
	{
		ft_putstr_fd("ERROR : Open() error\n", fd);
	}
	write(fd, &stop, sizeof(stop));
}

t_bool	command_ls(int fd, char *command, char *curdir)
{
	if (ft_strequ(command, "ls"))
	{
		show_ls(fd, curdir);
		return (TRUE);
	}
	return (FALSE);
}

t_bool	command_pwd(int fd, char *command, char *curdir)
{
	char *tmp;

	if (ft_strequ(command, "pwd"))
	{
		if (!(tmp = ft_strjoin_multi(FALSE, "SUCCESS : ", curdir, NULL)))
			exit(0);
		ft_putstr_fd(tmp, fd);
		ft_strdel(&tmp);
		return (TRUE);
	}
	return (FALSE);
}

t_bool	command_get(int fd, char *command, char *curdir)
{
	char *path;
	char *file;

	if (ft_strlen(command) <= 4)
		return (FALSE);
	if (0 != ft_memcmp(command, "get ", 4))
		return (FALSE);
	if (!(path = ft_strdup((command) + 4)))
		exit(0);
	if (ft_strequ("..", path))
		return (FALSE);
	if (NULL != ft_strstr(path, "/"))
		return (FALSE);
	if (!(file = ft_strjoin_multi(TRUE, ft_strdup(curdir),
		ft_strdup("/"), path, NULL)))
		exit(0);
	if (!can_read(file))
	{
		ft_putstr_fd("ERROR : Can't read.", fd);
		return (TRUE);
	}
	send_file(file, fd);
	ft_strdel(&file);
	return (TRUE);
}
