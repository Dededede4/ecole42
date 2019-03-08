/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_get.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mprevot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/08 19:30:22 by mprevot           #+#    #+#             */
/*   Updated: 2019/03/08 19:30:26 by mprevot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "client.h"

void	command_get_inside(int fd, char **file)
{
	char	*tmp;
	off_t	filesize;

	tmp = NULL;
	if (ft_gnl(fd, &tmp))
	{
		if (ft_strequ(tmp, "takefile"))
		{
			ft_strdel(&tmp);
			if (ft_gnl(fd, &tmp))
			{
				filesize = ft_atoi_offt(tmp);
				download_file(fd, *file, filesize);
			}
		}
		else
			ft_printf("%s\n", tmp);
		ft_strdel(&tmp);
	}
	ft_strdel(file);
}

t_bool	command_get(int fd, char *command)
{
	char *file;

	if (ft_strlen(command) <= 4)
		return (FALSE);
	if (0 != ft_memcmp(command, "get ", 4))
		return (FALSE);
	if (!(file = ft_strdup((command) + 4)))
	{
		ft_strdel(&file);
		exit(0);
	}
	ft_putstr_fd(command, fd);
	command_get_inside(fd, &file);
	return (TRUE);
}
