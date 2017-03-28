/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   corewar_end_music.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gnebie <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/28 06:53:56 by gnebie            #+#    #+#             */
/*   Updated: 2017/03/28 06:53:57 by gnebie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/types.h>
#include <signal.h>
#include "corewar.h"

void			corewar_end_music(t_datas *datas, int i)
{
	if (datas->pid[i] != -1 && datas->pid[i] != 0 && datas->pid[i] != 1)
		kill((pid_t)datas->pid[i], SIGTERM);
}
