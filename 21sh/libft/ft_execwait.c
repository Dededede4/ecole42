/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_execwait.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mprevot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/10 21:42:34 by mprevot           #+#    #+#             */
/*   Updated: 2017/08/10 21:42:44 by mprevot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void		ft_execwait(char *path, char **av)
{
	pid_t	father;
	int		osef;
	char	**pcur;

	osef = 0;
	father = fork();
	if (father > 0)
		wait(&osef);
	else
	{
		pcur = ft_getpcur();
		execve(path, av, pcur);
		ft_strsplit_del(&pcur);
	}
}
