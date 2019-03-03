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

#include "libft/libft.h"
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <dirent.h>
#include <sys/types.h> 
#include <sys/stat.h> 

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

void	print(int cs)
{
	char *line;
	char *curdir;

	line = NULL;
	curdir = ft_strdup(".");
	while (ft_gnl(cs, &line))
	{
		ft_printf("%s\n", line);
		free(line);
	}
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

t_bool command_get(int fd, char *command)
{
	char *path;
	char *tmp;
	char *file;
	off_t filesize;

	if (ft_strlen(command) <= 4)
		return (FALSE);
	if (0 != ft_memcmp(command, "get ", 4))
		return (FALSE);
	file = ft_strdup((command) + 4);
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
				download_file(fd, file, filesize);
			}
		}
	}
	free(file);
	return (TRUE);
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

t_bool command_put(int fd, char *command)
{
	char *path;
	char *tmp;
	char *file;
	off_t filesize;

	if (ft_strlen(command) <= 4)
		return (FALSE);
	if (0 != ft_memcmp(command, "put ", 4))
		return (FALSE);
	file = ft_strdup((command) + 4);
	ft_putstr_fd(command, fd);
	send_file(file, fd);
	free(file);
	return (TRUE);
}

t_bool command_cd(int fd, char *command)
{
	char *path;
	char *tmp;
	char *file;
	off_t filesize;

	if (ft_strlen(command) <= 3)
		return (FALSE);
	if (0 != ft_memcmp(command, "cd ", 3))
		return (FALSE);
	ft_putstr_fd(command, fd);
	return (TRUE);
}

t_bool command_quit(int fd, char *command)
{
	char *path;
	char *tmp;
	char *file;
	off_t filesize;

	if (!ft_strequ(command, "quit"))
		return (FALSE);
	exit(0);
	return (TRUE);
}

t_bool command_pwd(int fd, char *command)
{
	char *path;
	char *tmp;
	char *file;
	off_t filesize;

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
		free(line);
		line = NULL;
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

	if (ac != 3)
		usage(av[0]);
	port = ft_atoi(av[2]);
	sock = create_client(av[1], port);

	prompt(sock);
	// ft_putstr_fd("ls", sock);
	// print(sock);
	close(sock);
	return (0);
}