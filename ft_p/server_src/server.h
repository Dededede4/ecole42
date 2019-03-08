/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mprevot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/06 15:24:47 by mprevot           #+#    #+#             */
/*   Updated: 2019/03/06 15:24:48 by mprevot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVER_H
# define SERVER_H

# include "../libft/libft.h"
# include "../share/share.h"
# include <sys/socket.h>
# include <netinet/in.h>
# include <arpa/inet.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <netdb.h>
# include <dirent.h>

void	usage(char *str);
int		create_server(int port);
t_bool	command_ls(int fd, char *command, char *curdir);
t_bool	command_pwd(int fd, char *command, char *curdir);
t_bool	command_get(int fd, char *command, char *curdir);
t_bool	command_put(int fd, char *command, char *curdir);
t_bool	command_cd(int fd, char *command, char **curdir);
void	speak(int cs);
int		main(int ac, char **av);

#endif
