/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_input_validate.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mprevot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/04 18:16:28 by mprevot           #+#    #+#             */
/*   Updated: 2018/02/04 18:16:31 by mprevot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../main.h"

t_bool			display_input_validate(unsigned int buff, t_command **command)
{
	t_command	*new_command;

	if ('\n' == buff)
	{
		ft_putchar('\n');
		t_restore();
		execute(*command);
		t_init(FALSE);
		ft_putstr("$> ");
		if (NULL == ((t_command *)(*command))->str ||
			'\0' == ((t_command *)(*command))->str[0])
			return (TRUE);
		(*command)->pos = ft_uintlen((*command)->str);
		new_command = ft_memalloc(sizeof(t_command));
		new_command->prev = (*command);
		new_command->prev->next = new_command;
		*command = new_command;
		return (TRUE);
	}
	return (FALSE);
}
