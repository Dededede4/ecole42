/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mprevot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/06 15:51:49 by mprevot           #+#    #+#             */
/*   Updated: 2019/03/06 15:51:51 by mprevot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CLIENT_H
# define CLIENT_H

# include "../libft/libft.h"
# include "../share/share.h"
# include <sys/socket.h>
# include <netinet/in.h>
# include <arpa/inet.h>
# include <netdb.h>
# include <dirent.h>
# include <sys/types.h>
# include <sys/stat.h>

void	usage(char *str);
int		create_client(char *addr, int port);
t_bool	command_get(int fd, char *command);
t_bool	command_put(int fd, char *command);
t_bool	command_cd(int fd, char *command);
t_bool	command_quit(int fd, char *command);
t_bool	command_pwd(int fd, char *command);
t_bool	command_ls(int fd, char *command);
void	translate(int fdout, char *line);
void	prompt(int fdout);
int		main(int ac, char **av);

#endif
