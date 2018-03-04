/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   complete_buff.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mprevot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/04 19:58:10 by mprevot           #+#    #+#             */
/*   Updated: 2018/02/04 19:58:18 by mprevot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../main.h"

void		pass1_values(unsigned int *buff, int newbuff)
{
	if (65 == newbuff)
		*buff = MOVE_TOP;
	if (66 == newbuff)
		*buff = MOVE_DOWN;
	if (67 == newbuff)
		*buff = MOVE_RIGHT;
	if (68 == newbuff)
		*buff = MOVE_LEFT;
	if (72 == newbuff)
		*buff = MOVE_HOME;
	if (70 == newbuff)
		*buff = MOVE_END;
}

void		pass2_values(unsigned int *buff, int newbuff)
{
	if (65 == newbuff)
		*buff = SUPERMOVE_UP;
	if (66 == newbuff)
		*buff = SUPERMOVE_DOWN;
	if (67 == newbuff)
		*buff = SUPERMOVE_RIGHT;
	if (68 == newbuff)
		*buff = SUPERMOVE_LEFT;
}

void		pass_values(unsigned int *buff, int *newbuff)
{
	read(STDIN_FILENO, newbuff, 1);
	if (91 == *newbuff)
	{
		read(STDIN_FILENO, newbuff, 1);
		pass1_values(buff, *newbuff);
	}
	else if (KEY_ESC == *newbuff)
	{
		read(STDIN_FILENO, newbuff, 1);
		if (91 == *newbuff)
		{
			read(STDIN_FILENO, newbuff, 1);
			pass2_values(buff, *newbuff);
		}
	}
	else if ('c' == *newbuff || 'p' == *newbuff || 'C' == *newbuff
		|| 's' == *newbuff)
	{
		*buff = *buff << 8;
		*buff = *buff | *newbuff;
	}
}

/*
**	if (*buff <= 127)
**		return;
**	if (*buff <= 223) // 1 octet en plus à lire
**		toadd = 1;
**	else if (*buff < 240) // 2 octets en plus à lire
**		toadd = 2;
**	else // 3 octets en plus à lire
**		toadd = 3;
*/

void		complete_buff(unsigned int *buff)
{
	int toadd;
	int toaddsave;
	int newbuff;

	newbuff = 0;
	toadd = 0;
	if (KEY_ESC == *buff)
	{
		pass_values(buff, &newbuff);
		return ;
	}
	if (*buff <= 127)
		return ;
	if (*buff <= 223)
		toadd = 1;
	else if (*buff < 240)
		toadd = 2;
	else
		toadd = 3;
	toaddsave = toadd;
	read(STDIN_FILENO, &newbuff, toaddsave);
	newbuff = newbuff << 8;
	*buff = newbuff | *buff;
}
