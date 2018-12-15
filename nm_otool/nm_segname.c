/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nm_segname.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mprevot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/15 03:29:51 by mprevot           #+#    #+#             */
/*   Updated: 2018/12/15 03:30:10 by mprevot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm.h"

void		segname2struct_switch(int ycount, t_list **data)
{
	t_list	*tmp;

	tmp = ft_lstnew(&ycount, 4);
	if (*data)
		tmp->next = *data;
	*data = tmp;
}

t_command	*get_command(void)
{
	static void	*ptr;

	if (!ptr)
		ptr = ft_memalloc(sizeof(t_command));
	return (ptr);
}

void		segname2struct(int ycount, char *sectname)
{
	t_command	*command;

	command = get_command();
	if (ft_strequ(sectname, "__bss"))
		segname2struct_switch(ycount, &(command->bss_numbers));
	else if (ft_strequ(sectname, "__data"))
		segname2struct_switch(ycount, &(command->data_numbers));
	else if (ft_strequ(sectname, "__text"))
		segname2struct_switch(ycount, &(command->text_numbers));
	else
		segname2struct_switch(ycount, &(command->const_numbers));
}
