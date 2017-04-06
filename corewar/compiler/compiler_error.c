/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   compiler_error.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mprevot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/24 14:29:59 by mprevot           #+#    #+#             */
/*   Updated: 2017/03/24 14:30:03 by mprevot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "compiler.h"

int				addline(void)
{
	static int	lines = 0;

	return (lines++);
}

int				gnl(const int fd, char **line)
{
	addline();
	return (ft_gnl(fd, line));
}

void			error(char *str)
{
	char		*strint;

	strint = ft_itoa(addline());
	ft_putstr_fd("Line ", STDERR_FILENO);
	ft_putstr_fd(strint, STDERR_FILENO);
	ft_putstr_fd(" : ", STDERR_FILENO);
	ft_putstr_fd(str, STDERR_FILENO);
	exit(0);
}
