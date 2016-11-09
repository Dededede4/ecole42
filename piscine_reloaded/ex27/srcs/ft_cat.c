/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cat.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mprevot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/09 17:28:31 by mprevot           #+#    #+#             */
/*   Updated: 2016/11/09 17:43:05 by mprevot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/display_file.h"

void	ft_cat(char *path)
{
	int		i;
	int		fd;
	void	*buf[255];

	i = 0;
	fd = open(path, O_RDONLY);
	if (fd > -1)
	{
		while (read(fd, buf, 255) > 0)
		{
			write(1, buf, 255);	
		}
	}
	close(fd);
}
