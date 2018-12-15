/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nm_get_type.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mprevot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/15 03:16:13 by mprevot           #+#    #+#             */
/*   Updated: 2018/12/15 03:16:22 by mprevot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm.h"

t_bool	lookfor(uint8_t n_sect, t_list *lst)
{
	while (lst)
	{
		if (*((int*)((lst->content))) == n_sect)
			return (TRUE);
		lst = lst->next;
	}
	return (FALSE);
}

char	get_type_lookfor(uint8_t n_sect)
{
	char		c;
	t_command	*command;

	command = get_command();
	if (lookfor(n_sect, command->bss_numbers))
		c = 'B';
	else if (lookfor(n_sect, command->const_numbers))
		c = 'S';
	else if (lookfor(n_sect, command->data_numbers))
		c = 'D';
	else if (lookfor(n_sect, command->text_numbers))
		c = 'T';
	else
		c = '?';
	return (c);
}

char	get_type(struct nlist_64 el)
{
	t_bool	upper;
	char	c;

	upper = (0 != (el.n_type & N_EXT));
	if (0 != (el.n_type & N_STAB))
		c = '-';
	else if (N_UNDF == (el.n_type & N_TYPE))
	{
		if (el.n_value)
			c = 'C';
		else
			c = 'U';
	}
	else if (N_ABS == (el.n_type & N_TYPE))
		c = 'A';
	else if (N_INDR == (el.n_type & N_TYPE))
		c = 'I';
	else if (el.n_desc & N_WEAK_REF)
		c = 'W';
	else
		c = get_type_lookfor(el.n_sect);
	if (upper)
		return (c);
	return (ft_tolower(c));
}

char	get_type_32(struct nlist el)
{
	t_bool	upper;
	char	c;

	upper = (0 != (el.n_type & N_EXT));
	if (0 != (el.n_type & N_STAB))
		c = '-';
	else if (N_UNDF == (el.n_type & N_TYPE))
	{
		if (el.n_value)
			c = 'C';
		else
			c = 'U';
	}
	else if (N_ABS == (el.n_type & N_TYPE))
		c = 'A';
	else if (N_INDR == (el.n_type & N_TYPE))
		c = 'I';
	else if (el.n_desc & N_WEAK_REF)
		c = 'W';
	else
		c = get_type_lookfor(el.n_sect);
	if (upper)
		return (c);
	return (ft_tolower(c));
}
