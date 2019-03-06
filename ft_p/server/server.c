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
	ft_memdel((void**)&proto);
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

int show_ls(int fd, char *path)
{
  DIR			*d;
  struct dirent *dir;
  int stop = 0x0A00E00A; // REV(\n 57 344 \n)

  d = opendir(path);
  if (d) {
    while ((dir = readdir(d)) != NULL) {
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

t_bool command_pwd(int fd, char *command, char *curdir)
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


t_bool command_get(int fd, char *command, char *curdir)
{
	char *path;
	char *file;

	if (ft_strlen(command) <= 4)
		return (FALSE);
	if (0 != ft_memcmp(command, "get ", 4))
		return (FALSE);
	if(!(path = ft_strdup((command) + 4)))
		exit(0);
	if (ft_strequ(".." , path))
		return (FALSE);
	if (NULL != ft_strstr(path, "/" ))
		return (FALSE);
	
	if(!(file = ft_strjoin_multi(TRUE, ft_strdup(curdir), ft_strdup("/"), path, NULL)))
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

t_bool command_put(int fd, char *command, char *curdir)
{
	char *path;
	char *tmp;
	char *file;
	off_t filesize;

	if (ft_strlen(command) <= 4)
		return (FALSE);
	if (0 != ft_memcmp(command, "put ", 4))
		return (FALSE);
	if (!(path = ft_strdup((command) + 4)))
		exit(0);
	if (!(file = ft_strjoin_multi(TRUE, ft_strdup(curdir), ft_strdup("/"), path, NULL)))
		exit(0);
	tmp = NULL;
	if (!can_write(file))
	{
		ft_strdel(&file);
		ft_putstr_fd("ERROR : Can't write.\n", fd);
		return (TRUE);
	}
	if(ft_gnl(fd, &tmp))
	{
		if (ft_strequ(tmp, "takefile"))
		{
			ft_memdel((void**)&tmp);
			if(ft_gnl(fd, &tmp))
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
	ft_strdel(&file);
	return (TRUE);
}


t_bool command_cd(int fd, char *command, char **curdir)
{
	char *path;

	(void)fd;
	if (ft_strlen(command) <= 3)
		return (FALSE);
	if (0 != ft_memcmp(command, "cd ", 3))
		return (FALSE);
	if(!(path = ft_strdup((command) + 3)))
		exit(0);
	if (ft_strequ(".." , path))
	{
		ft_strdel(&path);
		return (FALSE);
	}
	if (NULL != ft_strstr(path, "/" ))
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
	ft_printf("(path) : %s \n", path);
	if (ft_strequ("." , path))
	{
		ft_putstr_fd("SUCCESS\n", fd);
		free(*curdir);
		*curdir = path;
		return (TRUE);
	}
	if(!(*curdir = ft_strjoin_multi(TRUE, *curdir, ft_strdup("/"), path, NULL)))
		exit(0);
	ft_putstr_fd("SUCCESS\n", fd);
	return (TRUE);
}


void	speak(int cs)
{
	char *line;
	char *curdir;
	int ret;

	line = NULL;
	curdir = ft_strdup(".");
	while ((ret = ft_gnl(cs, &line)))
	{
		if (command_ls(cs, line, curdir))
			;
		else if (command_cd(cs, line, &curdir))
		{
			;
		}
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
			close(sock);
			ft_printf("Nouvelle connexion.\n");
			while (1)
				speak(cs);
		}
	}
	close(sock);
	return (0);
}