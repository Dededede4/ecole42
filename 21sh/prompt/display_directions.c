/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_directions.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mprevot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/04 10:28:20 by mprevot           #+#    #+#             */
/*   Updated: 2018/02/04 10:28:21 by mprevot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../main.h"

t_bool	display_input_left(unsigned int buff, t_command *command)
{
	if (4479771 == buff)
	{
		if (command->pos == 0)
			return (TRUE);
		if (command->pos > 0)
			command->pos--;
		t_move_left();
		return (TRUE);
	}
	return (FALSE);
}

t_bool	display_input_right(unsigned int buff, t_command *command)
{
	struct winsize		w;

	ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
	if (4414235 == buff)
	{
		if (command->pos == ft_uintlen(command->str))
			return (TRUE);
		if ((command->pos < w.ws_col && command->pos + 3 == w.ws_col) ||
			(command->pos > w.ws_col && command->pos % w.ws_col == 0))
		{
			tputs(tgetstr("do", NULL), 1, ft_putchar2);
			tputs(tgoto(tgetstr("ch", NULL), 0, 0), 1, ft_putchar2);
			tputs(tgetstr("nd", NULL), 1, ft_putchar2);
		}
		else
			tputs(tgetstr("nd", NULL), 1, ft_putchar2);
		command->pos++;
		return (TRUE);
	}
	return (FALSE);
}
