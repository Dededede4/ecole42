/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_others.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mprevot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/08 19:37:40 by mprevot           #+#    #+#             */
/*   Updated: 2019/03/08 19:37:43 by mprevot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "client.h"

t_bool	command_put(int fd, char *command)
{
	char *file;
	char *commandnl;

	if (ft_strlen(command) <= 4)
		return (FALSE);
	if (0 != ft_memcmp(command, "put ", 4))
		return (FALSE);
	if (!(file = ft_strdup((command) + 4)))
		exit(0);
	if (!can_read(file))
	{
		ft_printf("Cannot read the file.\n");
		ft_strdel(&file);
		return (TRUE);
	}
	if (!(commandnl =
		ft_strjoin_multi(TRUE, ft_strdup(command), ft_strdup("\n"), NULL)))
		exit(0);
	ft_putstr_fd(commandnl, fd);
	ft_strdel(&commandnl);
	send_file(file, fd);
	ft_strdel(&file);
	displayline(fd);
	return (TRUE);
}

t_bool	command_cd(int fd, char *command)
{
	char *tmp;

	if (ft_strlen(command) <= 3)
		return (FALSE);
	if (0 != ft_memcmp(command, "cd ", 3))
		return (FALSE);
	ft_putstr_fd(command, fd);
	tmp = NULL;
	ft_gnl(fd, &tmp);
	if (tmp)
		ft_printf("%s\n", tmp);
	ft_strdel(&tmp);
	return (TRUE);
}

t_bool	command_quit(int fd, char *command)
{
	(void)fd;
	if (!ft_strequ(command, "quit"))
		return (FALSE);
	exit(0);
	return (TRUE);
}

t_bool	command_pwd(int fd, char *command)
{
	char *tmp;

	if (ft_strlen(command) != 3)
		return (FALSE);
	if (0 != ft_memcmp(command, "pwd", 3))
		return (FALSE);
	ft_putstr_fd(command, fd);
	tmp = NULL;
	if (ft_gnl(fd, &tmp))
	{
		ft_printf("%s\n", tmp);
	}
	ft_strdel(&tmp);
	return (TRUE);
}

t_bool	command_ls(int fd, char *command)
{
	char *tmp;

	if (!ft_strequ(command, "ls"))
		return (FALSE);
	tmp = NULL;
	ft_putstr_fd(command, fd);
	while (ft_gnl(fd, &tmp))
	{
		if ((unsigned char)tmp[0] == 0xE0 && tmp[1] == 00)
		{
			ft_printf("\n");
			break ;
		}
		ft_printf("%s", tmp);
		ft_strdel(&tmp);
	}
	ft_strdel(&tmp);
	return (TRUE);
}
