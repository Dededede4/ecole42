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

#include "../main.h"

struct termios attrib_old;

void				t_init(t_bool save)
{
	char			*name_term;
	struct termios	tattr;

	if ((name_term = ft_getenv("TERM")) == NULL)
		exit(0);
	if (tgetent(NULL, name_term) == ERR)
		exit(0);
	if (save)
		t_save();
	tcgetattr(STDIN_FILENO, &tattr);
	tattr.c_lflag &= ~(ICANON);
	tattr.c_lflag &= ~(ECHO);
	tattr.c_cc[VMIN] = 1;
	tattr.c_cc[VTIME] = 0;
	tcsetattr(STDIN_FILENO, TCSADRAIN, &tattr);
}

void				t_save(void)
{
	tcgetattr(STDIN_FILENO, &attrib_old);
}

void				t_restore(void)
{
	tcsetattr(STDIN_FILENO, TCSADRAIN, &attrib_old);
}
