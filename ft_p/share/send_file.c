/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   send_file.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mprevot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/05 18:24:48 by mprevot           #+#    #+#             */
/*   Updated: 2019/03/05 18:24:49 by mprevot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "share.h"

void	send_file(char *file, int fd)
{
	struct stat	st;
	off_t		size;
	char		buff[1024];
	int			r;
	int			fdfile;

	ft_putstr_fd("takefile\n", fd);
	stat(file, &st);
	size = st.st_size;
	ft_putofft_fd(size, fd);
	fdfile = open(file, O_RDONLY);
	ft_printf("%d %s\n", fdfile, file);
	ft_sleep();
	while ((r = read(fdfile, buff, 1024)) > 0)
	{
		write(fd, buff, r);
		write(1, buff, r);
	}
	close(fdfile);
}
