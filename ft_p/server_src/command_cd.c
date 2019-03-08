/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mprevot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/08 19:06:29 by mprevot           #+#    #+#             */
/*   Updated: 2019/03/08 19:06:33 by mprevot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"

t_bool	command_cd_inside(int fd, char **curdir, char *path)
{
	ft_printf("(path) : %s \n", path);
	if (ft_strequ(".", path))
	{
		ft_putstr_fd("SUCCESS\n", fd);
		free(*curdir);
		*curdir = path;
		return (TRUE);
	}
	if (!(*curdir = ft_strjoin_multi(TRUE, *curdir,
		ft_strdup("/"), path, NULL)))
		exit(0);
	ft_putstr_fd("SUCCESS\n", fd);
	return (TRUE);
}

t_bool	command_cd(int fd, char *command, char **curdir)
{
	char *path;

	if (ft_strlen(command) <= 3)
		return (FALSE);
	if (0 != ft_memcmp(command, "cd ", 3))
		return (FALSE);
	if (!(path = ft_strdup((command) + 3)))
		exit(0);
	if (ft_strequ("..", path))
	{
		ft_strdel(&path);
		return (FALSE);
	}
	if (NULL != ft_strstr(path, "/"))
	{
		ft_strdel(&path);
		return (FALSE);
	}
	if (!is_dir(path))
	{
		ft_putstr_fd("ERROR : Is not a dir.\n", fd);
		ft_strdel(&path);
		return (TRUE);
	}
	return (command_cd_inside(fd, curdir, path));
}
