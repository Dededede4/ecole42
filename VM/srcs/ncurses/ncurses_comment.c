/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ncurses_comment.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntoniolo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/22 00:08:04 by ntoniolo          #+#    #+#             */
/*   Updated: 2017/03/27 14:15:04 by ntoniolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void		print_comment(t_datas *datas, t_nc *nc)
{
	static int	size_s = 1;
	static int	more = 0;

	(void)datas;
	if (more >= nc->len_com - 60)
		mvwprintw(nc->inf, 13, 2, "%*.*s", 60, size_s, nc->str_com);
	if (more <= nc->len_com)
		mvwprintw(nc->inf, 13, 2, "%.*s", 60, &nc->str_com[more]);
	if (((nc->t2.tv_usec - nc->t1.tv_usec) > 100000 ||
											nc->t2.tv_sec - nc->t1.tv_sec))
	{
		gettimeofday(&nc->t1, NULL);
		if (size_s <= 60 && more >= nc->len_com - 60)
			size_s++;
		else
			size_s = 1;
		if (more == nc->len_com)
			more = 0;
		more++;
	}
	gettimeofday(&nc->t2, NULL);
}
