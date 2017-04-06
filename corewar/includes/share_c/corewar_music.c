/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   corewar_music.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gnebie <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/28 02:46:39 by gnebie            #+#    #+#             */
/*   Updated: 2017/03/28 02:46:41 by gnebie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <dirent.h>
#include <sys/types.h>

static pid_t		corewar_create_process(void)
{
	pid_t	pid;

	while (((pid = fork()) == -1) && (errno == EAGAIN))
		;
	return (pid);
}

void				son_process(char *arg[])
{
	if (execv("/usr/bin/afplay", arg) == -1)
	{
		perror("execv");
		exit(EXIT_FAILURE);
	}
}

int					corewar_music(t_datas *datas, int i, int (*f)(t_datas *))
{
	pid_t	pid;
	char	*arg[4];

	arg[0] = "afplay";
	if (i == 1)
		arg[1] = "./music/Heros.mp3";
	else if (i == 2)
		arg[1] = "./music/kill.mp3";
	else if (i == 3)
		arg[1] = "./music/ffvii.mp3";
	else
		arg[1] = "./music/ffvii.mp3";
	arg[2] = NULL;
	pid = corewar_create_process();
	if (pid == 0)
		son_process(arg);
	else
		datas->pid[i] = pid;
	return (f(datas));
}
