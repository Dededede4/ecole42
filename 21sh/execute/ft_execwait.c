/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_execwait.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mprevot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/16 19:36:47 by mprevot           #+#    #+#             */
/*   Updated: 2018/02/16 19:36:55 by mprevot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../main.h"

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
