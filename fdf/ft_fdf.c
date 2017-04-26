/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fdf.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mprevot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/26 16:36:29 by mprevot           #+#    #+#             */
/*   Updated: 2017/04/26 16:36:31 by mprevot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void		ft_error(char *str)
{
	ft_putstr_fd(str, STDERR_FILENO);
	exit(0);
}

void		ft_strsplit_del(char ***str)
{
	int		i;
	char	*line;

	i = 0;
	while ((*str)[i])
	{
		line = (*str)[i];
		ft_strdel(&line);
		i++;
	}
	line = (*str)[i];
	ft_strdel(&line);
	free(*str);
	*str = NULL;
}
