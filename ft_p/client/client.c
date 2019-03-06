/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mprevot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/03 19:53:53 by mprevot           #+#    #+#             */
/*   Updated: 2019/03/03 19:53:57 by mprevot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "client.h"

void usage(char *str)
{
	ft_printf("Usage: %s <addr> <port>\n", str);
	exit(-1);
}

int create_client(char *addr, int port)
{
	int sock;
	struct protoent		*proto;
	struct sockaddr_in	sin;

	if (0 == (proto = getprotobyname("tcp")))
		return (-1);
	sock = socket(PF_INET, SOCK_STREAM, proto->p_proto);
	sin.sin_family = AF_INET;
	sin.sin_port = htons(port);
	sin.sin_addr.s_addr = inet_addr(addr);
	if (connect(sock, (struct sockaddr *)&sin, sizeof(sin)) == -1)
	{
		ft_printf("Connect error\n");
		exit(0);
	}
	return (sock);
}

t_bool command_get(int fd, char *command)
{
	char *tmp;
	char *file;
	off_t filesize;

	if (ft_strlen(command) <= 4)
		return (FALSE);
	if (0 != ft_memcmp(command, "get ", 4))
		return (FALSE);
	if(!(file = ft_strdup((command) + 4)))
		exit(0);
	ft_putstr_fd(command, fd);
	tmp = NULL;
	if(ft_gnl(fd, &tmp))
	{
		if (ft_strequ(tmp, "takefile"))
		{
			ft_strdel(&tmp);
			if(ft_gnl(fd, &tmp))
			{
				filesize = ft_atoi_offt(tmp);
				download_file(fd, file, filesize);
			}
		}
		else
			ft_printf("%s\n", tmp);
		ft_strdel(&tmp);
	}
	ft_strdel(&file);
	return (TRUE);
}

t_bool command_put(int fd, char *command)
{
	char *file;
	char *commandnl;

	if (ft_strlen(command) <= 4)
		return (FALSE);
	if (0 != ft_memcmp(command, "put ", 4))
		return (FALSE);
	if(!(file = ft_strdup((command) + 4)))
		exit(0);
	if (!can_read(file))
	{
		ft_printf("Cannot read the file.\n");
		ft_strdel(&file);
		return (TRUE);
	}
	if(!(commandnl = ft_strjoin_multi(TRUE, ft_strdup(command), ft_strdup("\n"), NULL)))
		exit(0);
	ft_putstr_fd(commandnl, fd);
	ft_strdel(&commandnl);
	send_file(file, fd);
	ft_strdel(&file);
	return (TRUE);
}

t_bool command_cd(int fd, char *command)
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

t_bool command_quit(int fd, char *command)
{
	(void)fd;
	if (!ft_strequ(command, "quit"))
		return (FALSE);
	exit(0);
	return (TRUE);
}

t_bool command_pwd(int fd, char *command)
{
	char *tmp;

	if (ft_strlen(command) != 3)
		return (FALSE);
	if (0 != ft_memcmp(command, "pwd", 3))
		return (FALSE);
	ft_putstr_fd(command, fd);
	tmp = NULL;
	if(ft_gnl(fd, &tmp))
	{
		ft_printf("%s\n", tmp);
	}
	ft_strdel(&tmp);
	return (TRUE);
}


t_bool command_ls(int fd, char *command)
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
			break;
		}
		ft_printf("%s", tmp);
		ft_strdel(&tmp);
	}
	ft_strdel(&tmp);
	return (TRUE);
}

void translate(int fdout, char *line)
{

	if (command_get(fdout, line))
		;
	else if (command_cd(fdout, line))
		;
	else if (command_pwd(fdout, line))
		;
	else if (command_ls(fdout, line))
		;
	else if (command_quit(fdout, line))
		;
	else if (command_put(fdout, line))
		;
	else
		ft_printf("Command no found.\n");
}

void prompt(int fdout)
{
	char *line;

	line = NULL;
	ft_printf("ft_p > ");
	while (ft_gnl(STDIN_FILENO, &line))
	{

		translate(fdout, line);
		ft_printf("ft_p > ");
		ft_strdel(&line);
	}
}


int	main(int ac, char **av)
{
	int port;
	int sock;

	if (ac != 3)
		usage(av[0]);
	port = ft_atoi(av[2]);
	sock = create_client(av[1], port);
	prompt(sock);
	close(sock);
	return (0);
}