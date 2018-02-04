/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_termcaps.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mprevot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/04 10:03:05 by mprevot           #+#    #+#             */
/*   Updated: 2018/02/04 10:03:06 by mprevot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

struct termios attrib_old;

void				t_init(void)
{
	char			*name_term;
	struct termios	term;

	if ((name_term = ft_getenv("TERM")) == NULL)
		exit(0);
	if (tgetent(NULL, name_term) == ERR)
		exit(0);
	if (tcgetattr(0, &term) == -1)
		exit(0);
	term.c_lflag &= ~(ICANON);
	term.c_lflag &= ~(ECHO);
	term.c_cc[VMIN] = 1;
	term.c_cc[VTIME] = 0;
	if (tcsetattr(0, TCSADRAIN, &term) == -1)
		exit(0);
}

void				t_save(void)
{
	tcgetattr(0, &attrib_old);
}

void				t_restore(void)
{
	tcsetattr(0, TCSANOW, &attrib_old);
}
