/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_put.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mprevot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/08 18:38:14 by mprevot           #+#    #+#             */
/*   Updated: 2019/03/08 18:38:15 by mprevot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"

void	command_put_inside(int fd, char *file)
{
	off_t	filesize;
	char	*tmp;

	tmp = NULL;
	if (ft_gnl(fd, &tmp))
	{
		if (ft_strequ(tmp, "takefile"))
		{
			ft_memdel((void**)&tmp);
			if (ft_gnl(fd, &tmp))
			{
				filesize = ft_atoi_offt(tmp);
				download_file(fd, file, filesize);
			}
			else
				ft_putstr_fd("ERROR : No filesize.\n", fd);
		}
		else
			ft_putstr_fd("ERROR : No TAKEFILE.\n", fd);
		ft_strdel(&tmp);
	}
}

t_bool	command_put(int fd, char *command, char *curdir)
{
	char	*path;
	char	*file;

	if (ft_strlen(command) <= 4)
		return (FALSE);
	if (0 != ft_memcmp(command, "put ", 4))
		return (FALSE);
	if (!(path = ft_strdup((command) + 4)))
		exit(0);
	if (!(file = ft_strjoin_multi(TRUE, ft_strdup(curdir),
		ft_strdup("/"), path, NULL)))
		exit(0);
	if (!can_write(file))
	{
		ft_strdel(&file);
		command_put_inside(fd, "/dev/null");
		ft_putstr_fd("ERROR : Can't write. (directory ? \
			The file already exists ?)\n", fd);
		return (TRUE);
	}
	command_put_inside(fd, file);
	ft_strdel(&file);
	ft_putstr_fd("SUCCESS\n", fd);
	return (TRUE);
}
