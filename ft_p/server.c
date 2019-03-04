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



int		ft_offtlen(off_t n)
{
	int			len;

	len = 1;
	if (n < 0)
		len++;
	while (n /= 10)
		len++;
	return (len);
}


char			*ft_itoa_offt_nl(off_t n)
{
	char		*str;
	int			len;

	len = ft_offtlen(n);
	str = ft_strnew(len + 1);
	str[len] = '\n';
	if (str == NULL)
		return (NULL);
	if (n < 0)
		str[0] = '-';
	else
		n = 0 - n;
	while (n / 10)
	{
		str[--len] = (0 - (n % 10)) + '0';
		n /= 10;
	}
	str[--len] = (0 - (n % 10)) + '0';

	return (str);
}

void	ft_putofft_fd(off_t n, int fd)
{
	char *tmp;

	tmp = ft_itoa_offt_nl(n);
	ft_putstr_fd(tmp, fd);
	free(tmp);
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
	
	fdfile = open(file, O_RDONLY);
	while((r = read(fdfile, buff, 1024)))
	{
		write(fd, buff, r);
	}
}

t_bool command_get(int fd, char *command, char *curdir)
{
	char *path;
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
	off_t   todownload;
	int 	r;

	todownload = filesize;
	fdout = open(filename, O_CREAT | O_WRONLY | O_TRUNC, 0666);
	downloaded = 0;
	ft_printf("start");
	while(downloaded < filesize)
	{
		if (todownload >= 1024)
			r = read(fdin, buff, 1024);
		else
			r = read(fdin, buff, todownload);
		if (-1 == r || 0 == r)
			break;
		ft_putstr_fd("AAAAAAAAA", 1);
		write(1, buff, r);
		write(fdout, buff, r);
		ft_printf("--------->%d\n", downloaded);
		downloaded += r;
		todownload -= r;
		ft_printf("--------->%d\n", downloaded);
	}
	close(fdout);
	ft_printf("fini");
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
	tmp = NULL;
	if(ft_gnl(fd, &tmp))
	{
		if (ft_strequ(tmp, "takefile"))
		{
			ft_memdel((void**)&tmp);
			if(ft_gnl(fd, &tmp))
			{
				filesize = ft_atoi_offt(tmp);
				ft_printf("->>%d<--\n", (int)filesize);
				download_file(fd, file, filesize);
			}
			else
			{
				ft_printf("lol c bug");
				exit(0);
			}
		}
		else
		{
			ft_printf("PAS DE TAKEFILE\n");
			exit(0);
		}
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
	int ret;

	line = NULL;
	curdir = ft_strdup(".");
	while ((ret = ft_gnl(cs, &line)))
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
		ft_strdel(&line);
	}
	ft_printf("Speak end");
	if (ret == -1 || ret == 0)
	{
		ft_printf("bye bye");
		exit(0);
	}
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
	cs = accept(sock, (struct sockaddr*)&csin, &cslen);
	while (1)
		speak(cs);
	exit(0);
	while (1)
	{
		cs = accept(sock, (struct sockaddr*)&csin, &cslen);
		pid = fork();
		if (pid == 0)
		{
			close(sock);
			ft_printf("NOUVEAU CHILD");
			while (1)
				speak(cs);
		}
	}
	close(sock);
	return (0);
}