/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   displayline.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mprevot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/09 01:33:33 by mprevot           #+#    #+#             */
/*   Updated: 2019/03/09 01:33:48 by mprevot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "share.h"

void	displayline(int fd)
{
	char *tmp;

	tmp = NULL;
	ft_gnl(fd, &tmp);
	ft_putstr_fd(tmp, 1);
	ft_putstr_fd("\n", 1);
	ft_strdel(&tmp);
}
