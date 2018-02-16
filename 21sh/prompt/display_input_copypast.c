/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_input_copypast.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mprevot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/04 19:22:11 by mprevot           #+#    #+#             */
/*   Updated: 2018/02/04 19:22:13 by mprevot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../main.h"

t_bool		display_input_copypast_cut(
	unsigned int buff, t_command *command, unsigned int **clipboard)
{
	size_t	min;
	size_t	max;

	if (command->cc_mode_enabled && ACTION_CUT == buff)
	{
		command->cc_pos_stop = command->pos;
		command->cc_mode_enabled = FALSE;
		ft_memdel((void**)clipboard);
		min = (command->cc_pos_start < command->cc_pos_stop) ?
			command->cc_pos_start : command->cc_pos_stop;
		max = (command->cc_pos_start < command->cc_pos_stop) ?
			command->cc_pos_stop : command->cc_pos_start;
		*clipboard = ft_memalloc((max - min + 1) * 4);
		ft_memcpy(*clipboard, command->str + min, (max - min) * 4);
		if (command->pos == min)
		{
			while (command->pos != max)
				display_input_right(MOVE_RIGHT, command);
		}
		while (command->pos != min)
			display_input_ondelete(127, command);
		return (TRUE);
	}
	return (FALSE);
}

t_bool		display_input_copypast_copy(
	unsigned int buff, t_command *command, unsigned int **clipboard)
{
	size_t min;
	size_t max;

	if (command->cc_mode_enabled && ACTION_COPY == buff)
	{
		command->cc_pos_stop = command->pos;
		command->cc_mode_enabled = FALSE;
		ft_memdel((void**)clipboard);
		min = (command->cc_pos_start < command->cc_pos_stop) ?
			command->cc_pos_start : command->cc_pos_stop;
		max = (command->cc_pos_start < command->cc_pos_stop) ?
			command->cc_pos_stop : command->cc_pos_start;
		*clipboard = ft_memalloc((max - min + 1) * 4);
		ft_memcpy(*clipboard, command->str + min, (max - min) * 4);
		return (TRUE);
	}
	return (FALSE);
}

t_bool		display_input_copypast_paste(
	unsigned int buff, t_command *command, unsigned int **clipboard)
{
	size_t	i;

	i = 0;
	if (ACTION_PAST == buff)
	{
		if (NULL != *clipboard)
		{
			while ((*clipboard)[i])
			{
				display_input_insert((*clipboard)[i], command);
				i++;
			}
		}
		return (TRUE);
	}
	return (FALSE);
}

t_bool		display_input_copypast(
	unsigned int buff, t_command *command, unsigned int **clipboard)
{
	if (ACTION_SELECT == buff)
	{
		command->cc_pos_start = command->pos;
		command->cc_mode_enabled = TRUE;
		return (TRUE);
	}
	if (display_input_copypast_paste(buff, command, clipboard))
		return (TRUE);
	if (display_input_copypast_copy(buff, command, clipboard))
		return (TRUE);
	if (display_input_copypast_cut(buff, command, clipboard))
		return (TRUE);
	return (FALSE);
}
