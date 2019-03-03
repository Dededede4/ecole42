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

#include "libft/libft.h"
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <dirent.h>
void usage(char *str)
{
	ft_printf("Usage: %s <port>\n", str);
	exit(-1);
}

int create_server(int port)
{
	int sock;
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

int show_ls(int fd, char *path) {
  DIR			*d;
  struct dirent *dir;

  d = opendir(path);
  if (d) {
    while ((dir = readdir(d)) != NULL) {
    	ft_putstr_fd(dir->d_name, fd);
    	ft_putstr_fd("\n", fd);
    }
    closedir(d);
  }
  return(0);
}

t_bool command_ls(int fd, char *command, char *curdir)
{
	if (ft_strequ(command, "ls"))
	{
		show_ls(fd, curdir);
		return (TRUE);
	}
	return (FALSE);
}

t_bool command_cd(int fd, char *command, char **curdir)
{
	char *path;
	char *tmp;

	if (ft_strlen(command) <= 3)
		return (FALSE);
	if (0 != ft_memcmp(command, "cd ", 3))
		return (FALSE);
	path = ft_strdup((command) + 3);
	if (ft_strequ(".." , path))
		return (FALSE);
	if (NULL != ft_strstr(path, "/" ))
		return (FALSE);
	ft_printf("(path) : %s \n", path);
	if (ft_strequ("." , path))
	{
		free(*curdir);
		*curdir = path;
		return (TRUE);
	}
	*curdir = ft_strjoin_multi(TRUE, *curdir, ft_strdup("/"), path, NULL);
	return (TRUE);
}


void	speak(int cs)
{
	char *line;
	char *curdir;

	line = NULL;
	curdir = ft_strdup(".");
	while (ft_gnl(cs, &line))
	{
		//ft_printf(line);
		if (command_ls(cs, line, curdir))
			;
		else if (command_cd(cs, line, &curdir))
		{
			ft_printf("Current : %s\n", curdir);
			;
		}
		else if (command_pwd(cs, line, curdir))
			;
		free(line);
		ft_putstr_fd("OK\n", cs);
	}
	ft_printf("Speak end");
}

int	main(int ac, char **av)
{
	int port;
	int sock;
	int cs;
	struct sockaddr_in csin;
	unsigned int 	cslen;
	pid_t pid;

	if (ac != 2)
		usage(av[0]);
	port = ft_atoi(av[1]);
	sock = create_server(port);
	while (1)
	{
		cs = accept(sock, (struct sockaddr*)&csin, &cslen);
		pid = fork();
		if (pid == 0)
		{
			speak(cs);
			close(cs);
		}
	}
	close(sock);
	return (0);
}