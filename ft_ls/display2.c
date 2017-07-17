/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mprevot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/17 20:47:40 by mprevot           #+#    #+#             */
/*   Updated: 2017/07/17 20:47:42 by mprevot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	long_display_1(t_path *pcur, t_file *file, t_params *params)
{
	if ((file && file->next && params->rr) ||
		params->rr || params->nbr_paths >= 2)
	{
		if (!(params->nbr_paths <= 1 &&
			ft_strcmp(pcur->path, params->paths->path) == 0))
		{
			if (pcur != params->paths)
				ft_putchar('\n');
			ft_printf("%s:\n", pcur->path);
		}
	}
}

void	long_display_while_1(t_file *file, t_width *width)
{
	ft_printf("%c%s  ", file->type, file->right);
	ft_putnbr_right(file->links, width->links);
	ft_putchar(' ');
	ft_putstr_left(file->owner, width->owner);
	ft_putstr("  ");
	ft_putstr_left(file->group, width->group);
	ft_putstr("  ");
}

void	long_display_while_2(t_file *file, t_width *width)
{
	ft_putnbr_right(file->major, width->major);
	ft_putstr(", ");
	ft_putnbr_right(file->minor, width->minor);
}

void	long_display_while_3(t_file *file)
{
	char		*linkname;
	ssize_t		r;

	ft_putstr(" -> ");
	linkname = ft_memalloc(10000 + 1);
	r = readlink(file->path, linkname, 10000 + 1);
	if (r < 0)
		exit(EXIT_FAILURE);
	if (r > 10000)
		exit(EXIT_FAILURE);
	linkname[10000] = '\0';
	ft_putstr(linkname);
}
