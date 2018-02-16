/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_supermoves.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mprevot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/04 10:31:55 by mprevot           #+#    #+#             */
/*   Updated: 2018/02/04 10:31:57 by mprevot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../main.h"

t_bool				display_input_supermoves_top(
	unsigned int buff, t_command *command)
{
	struct winsize	w;
	int				i;

	ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
	i = 0;
	if (buff == SUPERMOVE_UP)
	{
		while (i < w.ws_col)
		{
			display_input_left(MOVE_LEFT, command);
			i++;
		}
		return (TRUE);
	}
	return (FALSE);
}

t_bool				display_input_supermoves_down(
	unsigned int buff, t_command *command)
{
	struct winsize	w;
	int				i;

	ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
	i = 0;
	if (buff == SUPERMOVE_DOWN)
	{
		while (i < w.ws_col)
		{
			display_input_right(MOVE_RIGHT, command);
			i++;
		}
		return (TRUE);
	}
	return (FALSE);
}

t_bool				display_input_supermoves_right(
	unsigned int buff, t_command *command)
{
	struct winsize	w;
	int				i;

	ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
	i = 0;
	if (buff == SUPERMOVE_RIGHT)
	{
		display_input_right(MOVE_RIGHT, command);
		while (command->pos < ft_uintlen(command->str)
			&& ' ' != command->str[command->pos])
		{
			display_input_right(MOVE_RIGHT, command);
		}
		return (TRUE);
	}
	return (FALSE);
}

t_bool				display_input_supermoves_left(
	unsigned int buff, t_command *command)
{
	struct winsize	w;
	int				i;

	ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
	i = 0;
	if (buff == SUPERMOVE_LEFT)
	{
		if (command->pos != 0)
			display_input_left(MOVE_LEFT, command);
		while (command->pos != 0 && ' ' != command->str[command->pos])
		{
			display_input_left(MOVE_LEFT, command);
		}
		return (TRUE);
	}
	return (FALSE);
}

t_bool				display_input_supermoves(
	unsigned int buff, t_command *command)
{
	if (display_input_supermoves_top(buff, command))
		return (TRUE);
	if (display_input_supermoves_down(buff, command))
		return (TRUE);
	if (display_input_supermoves_right(buff, command))
		return (TRUE);
	if (display_input_supermoves_left(buff, command))
		return (TRUE);
	return (FALSE);
}
