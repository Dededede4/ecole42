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
	struct termios	tattr;

	if ((name_term = ft_getenv("TERM")) == NULL)
		exit(0);
	tcgetattr (STDIN_FILENO, &tattr);
	//tattr.c_lflag &= ~(ICANON|ECHO); /* Clear ICANON and ECHO. */
	tattr.c_lflag &= ~(ICANON);
	tattr.c_lflag &= ~(ECHO);
	tattr.c_cc[VMIN] = 1;
	tattr.c_cc[VTIME] = 0;
  	tcsetattr (STDIN_FILENO, TCSAFLUSH, &tattr);
}

void				t_save(void)
{	tcgetattr(0, &attrib_old);
}

void				t_restore(void)
{
	tcsetattr (STDIN_FILENO, TCSANOW, &attrib_old);
}
