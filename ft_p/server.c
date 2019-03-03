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
#include <sys/types.h> 
#include <sys/stat.h> 
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
	if (ft_strequ(command, "pwd"))
	{
		ft_putstr_fd(curdir, fd);
		return (TRUE);
	}
	return (FALSE);
}

void	ft_putofft_fd(off_t n, int fd)
{
	if (n >= 10)
	{
		ft_putnbr_fd(n / 10, fd);
		ft_putnbr_fd(n % 10, fd);
	}
	else
	{
		ft_putchar_fd(n + '0', fd);
	}
}

void send_file(char *file, int fd)
{
	struct stat st;
	off_t size;
	char	buff[1024];
	int 	r;
	int 	fdfile;

	ft_putstr_fd("takefile\n", fd);
	stat(file, &st);
	size = st.st_size;
	ft_putofft_fd(size, fd);
	ft_putchar_fd('\n', fd);
	fdfile = open(file, O_RDONLY);
	while((r = read(fdfile, buff, 1024)))
	{
		write(fd, buff, r);
	}
}

t_bool command_get(int fd, char *command, char *curdir)
{
	char *path;
	char *tmp;
	char *file;

	if (ft_strlen(command) <= 4)
		return (FALSE);
	if (0 != ft_memcmp(command, "get ", 4))
		return (FALSE);
	path = ft_strdup((command) + 4);
	if (ft_strequ(".." , path))
		return (FALSE);
	if (NULL != ft_strstr(path, "/" ))
		return (FALSE);
	
	file = ft_strjoin_multi(TRUE, ft_strdup(curdir), ft_strdup("/"), path, NULL);
	ft_printf("(file) : %s \n", file);
	send_file(file, fd);
	free(file);
	return (TRUE);
}

off_t			ft_atoi_offt(const char *str)
{
	off_t		result;
	off_t		n;

	n = 0;
	while (*str == '\n' || *str == '\t' || *str == '\v' \
			|| *str == ' ' || *str == '\f' || *str == '\r')
		str++;
	if (*str == '+')
		str++;
	result = 0;
	while (*str && *str >= '0' && *str <= '9')
	{
		result = (result * 10) - (*str - '0');
		str++;
	}
	if (n)
		return (result);
	else
		return (0 - result);
}

void download_file(int fdin, char *filename, off_t filesize)
{
	char	buff[1024];
	int		fdout;
	off_t	downloaded;
	int 	r;

	fdout = open(filename, O_CREAT | O_WRONLY | O_TRUNC, 0666);
	downloaded = 0;
	while((r = read(fdin, buff, 1024)))
	{
		ft_putstr_fd("AAAAAAAAA", 1);
		write(fdout, buff, r);
		downloaded += r;
		if (downloaded >= filesize)
			return ;
	}
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
	path = ft_strdup((command) + 4);
	file = ft_strjoin_multi(TRUE, ft_strdup(curdir), ft_strdup("/"), path, NULL);
	ft_putstr_fd(command, fd);
	tmp = NULL;
	if(ft_gnl(fd, &tmp))
	{
		if (ft_strequ(tmp, "takefile"))
		{
			ft_memdel((void**)&tmp);
			if(ft_gnl(fd, &tmp))
			{
				filesize = ft_atoi_offt(tmp);
				ft_putofft_fd(filesize, 1);
				download_file(fd, file, filesize);
			}
		}
	}
	ft_strdel(&path);
	ft_strdel(&file);
	return (TRUE);
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
	int stop;

	line = NULL;
	curdir = ft_strdup(".");
	while (ft_gnl(cs, &line))
	{
		ft_printf("\n New command : %s\n", line);
		if (command_ls(cs, line, curdir))
			;
		else if (command_cd(cs, line, &curdir))
		{
			ft_printf("Current : %s\n", curdir);
			;
		}
		else if (command_pwd(cs, line, curdir))
			;
		else if (command_get(cs, line, curdir))
			;
		else if (command_put(cs, line, curdir))
			;
		free(line);
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