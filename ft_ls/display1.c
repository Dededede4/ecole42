/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display1.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mprevot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/17 20:33:37 by mprevot           #+#    #+#             */
/*   Updated: 2017/07/17 20:33:40 by mprevot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void		set_width(t_width *width, t_file *file)
{
	if (width->links < (int)ft_intlen(file->links))
		width->links = (int)ft_intlen(file->links);
	if (width->owner < (int)ft_strlen(file->owner))
		width->owner = (int)ft_strlen(file->owner);
	if (width->group < (int)ft_strlen(file->group))
		width->group = (int)ft_strlen(file->group);
	if (width->bytes < (int)ft_intlen(file->bytes))
		width->bytes = (int)ft_intlen(file->bytes);
	if (!(file->type == 'c' || file->type == 'b'))
		return ;
	if (width->major < (int)ft_intlen(file->major))
		width->major = (int)ft_intlen(file->major);
	if (width->minor < (int)ft_intlen(file->minor))
		width->minor = (int)ft_intlen(file->minor);
	if (width->major + width->minor > width->bytes)
		width->bytes = width->major + width->minor;
}

t_width		*calculate_cols(t_file *file, t_params *params)
{
	t_width	*width;

	width = ft_memalloc(sizeof(*width));
	while (file)
	{
		if (!params->a && file->name[0] == '.')
		{
			file = file->next;
			continue;
		}
		set_width(width, file);
		file = file->next;
	}
	return (width);
}

void		sort_display(t_path *pcur, t_file *file, t_params *params)
{
	if ((((file && file->next && params->rr) || params->rr
		|| params->nbr_paths >= 2) && isdirectory(pcur->path))
		&& (!(params->nbr_paths <= 1 &&
			ft_strcmp(pcur->path, params->paths->path) == 0)))
	{
		if (pcur != params->paths)
			ft_putchar('\n');
		ft_printf("%s:\n", pcur->path);
	}
	if (file->error)
	{
		ft_putstr_error(file->error);
		return ;
	}
	while (file)
	{
		if (!params->a && file->name[0] == '.')
		{
			file = file->next;
			continue;
		}
		ft_putendl(file->name);
		file = file->next;
	}
}

void		ll_total(t_file *file, t_params *params)
{
	int			total;
	int			len;

	total = 0;
	len = 0;
	while (file)
	{
		if (params->a)
			total += file->blocks;
		else if (file->name[0] != '.')
			total += file->blocks;
		file = file->next;
		len++;
	}
	if (len > 2 || params->a)
		ft_printf("total %d\n", total);
}
