/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_input_historic.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mprevot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/04 18:21:54 by mprevot           #+#    #+#             */
/*   Updated: 2018/02/04 18:21:55 by mprevot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../main.h"

t_bool			display_input_historic_top(
	unsigned int buff, t_command *command)
{
	t_command	*goto_historic;

	if (MOVE_TOP == buff)
	{
		if (command->historic_pos)
			goto_historic = command->historic_pos->prev;
		else
			goto_historic = command->prev;
		if (!goto_historic)
			return (TRUE);
		clear_input(command);
		command->historic_pos = goto_historic;
		command->pos = 0;
		while (goto_historic->str[command->pos])
		{
			display_input_insert(goto_historic->str[command->pos], command);
		}
		return (TRUE);
	}
	return (FALSE);
}

t_bool			display_input_historic_down(
	unsigned int buff, t_command *command)
{
	t_command	*goto_historic;

	if (MOVE_DOWN == buff)
	{
		clear_input(command);
		if (NULL == command->historic_pos
			|| NULL == command->historic_pos->next)
			return (TRUE);
		goto_historic = command->historic_pos->next;
		if (NULL == goto_historic->str)
			return (TRUE);
		command->historic_pos = goto_historic;
		command->pos = 0;
		while (goto_historic->str[command->pos])
		{
			display_input_insert(goto_historic->str[command->pos], command);
		}
		return (TRUE);
	}
	return (FALSE);
}

t_bool			display_input_historic(unsigned int buff, t_command *command)
{
	if (display_input_historic_top(buff, command))
		return (TRUE);
	if (display_input_historic_down(buff, command))
		return (TRUE);
	return (FALSE);
}
