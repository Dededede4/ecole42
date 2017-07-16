/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mprevot <mprevot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/28 14:49:57 by mprevot           #+#    #+#             */
/*   Updated: 2014/12/05 15:47:15 by mprevot          ###   ########.fr       */
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

void	sort_display(t_path	*pcur, t_file *file, t_params *params)
{
	if (((file && file->next && params->R) || params->R || params->nbr_paths >= 2) && isDirectory(pcur->path))
	{
		if (!(params->nbr_paths <= 1 && ft_strcmp(pcur->path, params->paths->path) == 0))
		{
			if (pcur != params->paths)
				ft_putchar('\n');
			ft_printf("%s:\n", pcur->path);
		}
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
		file = file ->next;
	}
}

void	ll_total(t_file *file, t_params *params)
{
	int total;
	int len;
	struct stat fileStat;

	total = 0;
	len = 0;
	while(file)
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

void	ll_file_datetime(const time_t *clock)
{
	char	*str;
	char	**split;

	str = ctime(clock);

	//printf("\n(%s)\n", str);
	split = ft_strsplit(str, ' ');
	if (*clock > time(NULL) - (3600 * 24 * 30 * 6) && *clock <= time(NULL))
		ft_printf("%3s %2s %.5s", split[1], split[2], split[3]);
	else
		if (ft_atoi(split[4]) >= 10000)
			ft_printf("%3s %2s %6d", split[1], split[2], ft_atoi(split[4]));
		else
			ft_printf("%3s %2s %5d", split[1], split[2], ft_atoi(split[4]));
}


void long_display_1(t_path	*pcur, t_file *file, t_params *params)
{
	if ((file && file->next && params->R) || params->R || params->nbr_paths >= 2)
	{
		if (!(params->nbr_paths <= 1 && ft_strcmp(pcur->path, params->paths->path) == 0))

		{
			if (pcur != params->paths)
				ft_putchar('\n');
			ft_printf("%s:\n", pcur->path);
		}
	}
}

void long_display_while_1(t_file *file, t_width *width)
{
	ft_printf("%c%s  ", file->type, file->right);
	ft_putnbr_right(file->links, width->links);
	ft_putchar(' ');
	ft_putstr_left(file->owner, width->owner);
	ft_putstr("  ");
	ft_putstr_left(file->group, width->group);
	ft_putstr("  ");
} 

void long_display_while_2(t_file *file, t_width *width)
{
	ft_putnbr_right(file->major, width->major);
	ft_putstr(", ");
	ft_putnbr_right(file->minor, width->minor);
} 

void long_display_while_3(t_file *file)
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

void long_display_while(t_file *file, t_width *width, t_params *params)
{
	if (!params->a && file->name[0] == '.')
		return ;
	long_display_while_1(file, width);
	if (file->type == 'c' || file->type == 'b')
		long_display_while_2(file, width);
	else
		ft_putnbr_right(file->bytes, width->bytes);
	ft_putchar(' ');
	ll_file_datetime(&file->mtime);
	ft_printf(" %s", file->name);
	if (file->type == 'l')
		long_display_while_3(file);
	ft_putchar('\n');
	file = file ->next;
}

void    long_display(t_path	*pcur, t_file *file, t_params *params)
{
	t_width		*width;

	long_display_1(pcur, file, params);
	if (file->error)
	{
		ft_putstr_error(file->error);
		return ;
	}
	ll_total(file, params);
	width = calculate_cols(file, params);
	while (file)
	{
		long_display_while(file, width, params);
		file = file->next;
	}
}
