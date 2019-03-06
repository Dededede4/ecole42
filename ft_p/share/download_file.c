/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   download_file.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mprevot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/05 18:06:17 by mprevot           #+#    #+#             */
/*   Updated: 2019/03/05 18:06:18 by mprevot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "share.h"

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
