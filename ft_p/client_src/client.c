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

void	usage(char *str)
{
	ft_printf("Usage: %s <addr> <port>\n", str);
	exit(-1);
}

int		create_client(char *addr, int port)
{
	int					sock;
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

void	translate(int fdout, char *line)
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

void	prompt(int fdout)
{
	char	*line;

	line = NULL;
	ft_printf("ft_p > ");
	while (ft_gnl(STDIN_FILENO, &line))
	{
		translate(fdout, line);
		ft_printf("ft_p > ");
		ft_strdel(&line);
	}
}

int		main(int ac, char **av)
{
	int port;
	int sock;

	if (ac != 3)
		usage(av[0]);
	port = ft_atoi(av[2]);
	if (ft_strequ(av[1], "localhost"))
		sock = create_client("127.0.0.1", port);
	else
		sock = create_client(av[1], port);
	prompt(sock);
	close(sock);
	return (0);
}
