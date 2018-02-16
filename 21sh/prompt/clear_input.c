/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mprevot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/04 17:30:05 by mprevot           #+#    #+#             */
/*   Updated: 2018/02/04 17:30:09 by mprevot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../main.h"

void	clear_input(t_command *command)
{
	if (command->str == NULL)
		return ;
	while (command->pos != 0)
	{
		display_input_left(4479771, command);
	}
	t_delete_after_cursor();
	ft_memdel((void**)&(command->str));
}

void	clear_input_soft(t_command *command)
{
	if (command->str == NULL)
		return ;
	while (command->pos != 0)
	{
		display_input_left(4479771, command);
	}
	t_move_left();
	t_delete_after_cursor();
}
