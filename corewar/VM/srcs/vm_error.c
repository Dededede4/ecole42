/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_error.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gnebie <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/28 07:18:49 by gnebie            #+#    #+#             */
/*   Updated: 2017/03/28 07:18:51 by gnebie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

int			vm_error(t_datas *datas, const char *line)
{
	char	c;

	c = '\n';
	write(2, line, ft_strlen(line));
	write(2, &c, 1);
	if (datas->flag & FLAG_K && datas->flag & FLAG_M)
	{
		corewar_end_music(datas, 1);
		corewar_end_music(datas, 2);
		corewar_end_music(datas, 3);
	}
	return (-1);
}
