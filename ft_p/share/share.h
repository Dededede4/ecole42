/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   share.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mprevot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/06 15:36:16 by mprevot           #+#    #+#             */
/*   Updated: 2019/03/06 15:36:18 by mprevot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SHARE_H
# define SHARE_H

# include "../libft/libft.h"

# include <sys/socket.h>
# include <netinet/in.h>
# include <arpa/inet.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <netdb.h>
# include <dirent.h>

void	download_file(int fdin, char *filename, off_t filesize);
off_t	ft_atoi_offt(const char *str);
char	*ft_itoa_offt_nl(off_t n);
int		ft_offtlen(off_t n);
void	ft_putofft_fd(off_t n, int fd);
void	ft_sleep();
int		is_dir(char *p);
void	send_file(char *file, int fd);
t_bool	can_write(char *path);
t_bool	can_read(char *path);

#endif
