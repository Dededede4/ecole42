/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   antitroll_get_line.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mprevot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/15 03:56:11 by mprevot           #+#    #+#             */
/*   Updated: 2018/12/15 03:56:12 by mprevot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "antitroll.h"

t_line	*get_line_trololo(
	struct symtab_command *sym, char *ptr, off_t size)
{
	uint32_t		i;
	int				y;
	char			*stringtable;
	struct nlist_64	*el;
	char			*tmp;

	ifexit((size < sym->symoff), 50);
	el = (void*)ptr + sym->symoff;
	stringtable = ptr + sym->stroff;
	i = 0;
	while (i < sym->nsyms)
	{
		ifexit((size < sym->symoff +
			(off_t)sizeof(struct nlist_64) * (i + 1)), 51);
		ifexit((size < sym->stroff + el[i].n_un.n_strx + 1), 56);
		tmp = stringtable + el[i].n_un.n_strx;
		y = 0;
		ifexit(((void*)tmp >= (void*)ptr + size), 58);
		while (tmp[y])
			ifexit((tmp + (++y) + 1 >= ptr + size), 57);
		i++;
	}
	return (NULL);
}

t_line	*get_line_trololo_32(
	struct symtab_command *sym, char *ptr, off_t size)
{
	uint32_t		i;
	int				y;
	char			*stringtable;
	struct nlist	*el;
	char			*tmp;

	ifexit((size < sym->symoff), 50);
	el = (void*)ptr + sym->symoff;
	stringtable = ptr + sym->stroff;
	i = 0;
	while (i < sym->nsyms)
	{
		ifexit((size < sym->symoff +
			(off_t)sizeof(struct nlist) * (i + 1)), 51);
		ifexit((size < sym->stroff + el[i].n_un.n_strx + 1), 56);
		tmp = stringtable + el[i].n_un.n_strx;
		y = 0;
		ifexit(((void*)tmp >= (void*)ptr + size), 58);
		while (tmp[y])
			ifexit((tmp + (++y) + 1 >= ptr + size), 57);
		i++;
	}
	return (NULL);
}
