/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_input_delete_insert.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mprevot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/04 18:13:47 by mprevot           #+#    #+#             */
/*   Updated: 2018/02/04 18:13:49 by mprevot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../main.h"

t_bool	display_input_ondelete(unsigned int buff, t_command *command)
{
	size_t	savepos;

	if (buff == 127)
	{
		if (command->pos > 0)
			command->pos--;
		else
			return (TRUE);
		savepos = command->pos;
		clear_input_soft(command);
		ft_delete_char(&(command->str), savepos);
		show_command(command);
		while (savepos < command->pos)
		{
			display_input_left(4479771, command);
		}
		return (TRUE);
	}
	return (FALSE);
}

t_bool	display_input_insert(unsigned int buff, t_command *command)
{
	int				i;
	unsigned char	*b;
	size_t			savepos;

	b = (unsigned char*)&buff;
	i = 0;
	savepos = command->pos;
	t_delete_after_cursor();
	ft_insert_char(&(command->str), buff, command->pos);
	ft_uintput(command->str + command->pos);
	command->pos = ft_uintlen(command->str);
	savepos++;
	while (savepos < command->pos)
	{
		display_input_left(4479771, command);
	}
	return (TRUE);
}
