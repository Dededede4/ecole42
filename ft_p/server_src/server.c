/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mprevot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/03 15:15:41 by mprevot           #+#    #+#             */
/*   Updated: 2019/03/03 15:15:42 by mprevot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"

void	usage(char *str)
{
	ft_printf("Usage: %s <port>\n", str);
	exit(-1);
}

int		create_server(int port)
{
	int					sock;
	struct protoent		*proto;
	struct sockaddr_in	sin;

	if (0 == (proto = getprotobyname("tcp")))
		return (-1);
	sock = socket(PF_INET, SOCK_STREAM, proto->p_proto);
	sin.sin_family = AF_INET;
	sin.sin_port = htons(port);
	sin.sin_addr.s_addr = htonl(INADDR_ANY);
	if (bind(sock, (struct sockaddr *)&sin, sizeof(sin)) == -1)
	{
		ft_printf("Bind error\n");
		exit(0);
	}
	listen(sock, 42);
	return (sock);
}

void	speak(int cs)
{
	char	*line;
	char	*curdir;
	int		ret;

	line = NULL;
	curdir = ft_strdup(".");
	while ((ret = ft_gnl(cs, &line)))
	{
		if (command_ls(cs, line, curdir))
			;
		else if (command_cd(cs, line, &curdir))
			;
		else if (command_pwd(cs, line, curdir))
			;
		else if (command_get(cs, line, curdir))
			;
		else if (command_put(cs, line, curdir))
			;
		else
			ft_putstr_fd("Error : i don't understand what you mean bro.", cs);
		ft_strdel(&line);
	}
	if (ret == -1 || ret == 0)
		exit(0);
}

int		main(int ac, char **av)
{
	int					sock;
	int					cs;
	struct sockaddr_in	csin;
	unsigned int		cslen;
	pid_t				pid;

	if (ac != 2)
		usage(av[0]);
	sock = create_server(ft_atoi(av[1]));
	while (1)
	{
		cs = accept(sock, (struct sockaddr*)&csin, &cslen);
		pid = fork();
		if (pid == 0)
		{
			close(sock);
			ft_printf("Nouvelle connexion.\n");
			while (1)
				speak(cs);
		}
	}
	close(sock);
	return (0);
}
