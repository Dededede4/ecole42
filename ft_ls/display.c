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
		if (width->links < (int)ft_intlen(file->links))
			width->links = (int)ft_intlen(file->links);
		if (width->owner < (int)ft_strlen(file->owner))
			width->owner = (int)ft_strlen(file->owner);
		if (width->group < (int)ft_strlen(file->group))
			width->group = (int)ft_strlen(file->group);
		if (width->bytes < (int)ft_intlen(file->bytes))
			width->bytes = (int)ft_intlen(file->bytes);
		if (file->type == 'c' || file->type == 'b')
		{
			if (width->major < (int)ft_intlen(file->major))
				width->major = (int)ft_intlen(file->major);
			if (width->minor < (int)ft_intlen(file->minor))
				width->minor = (int)ft_intlen(file->minor);
			if (width->major + width->minor > width->bytes)
				width->bytes = width->major + width->minor;
		}
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

void    long_display(t_path	*pcur, t_file *file, t_params *params)
{
	t_width		*width;
	ssize_t		r;
	char		*linkname;

	if ((file && file->next && params->R) || params->R || params->nbr_paths >= 2)
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
	ll_total(file, params);
	width = calculate_cols(file, params);
	while (file)
	{
		if (!params->a && file->name[0] == '.')
		{
			file = file->next;
			continue;
		}
		ft_putchar(file->type);
		ft_putstr(file->right);
		ft_putstr("  ");
		ft_putstr_right(ft_itoa(file->links), width->links);
		ft_putchar(' ');
		ft_putstr_left(file->owner, width->owner);
		ft_putstr("  ");
		ft_putstr_left(file->group, width->group);
		ft_putstr("  ");
		if (file->type == 'c' || file->type == 'b')
		{
			ft_putstr_right(ft_itoa(file->major), width->major);
			ft_putstr(", ");
			ft_putstr_right(ft_itoa(file->minor), width->minor);
		}
		else
			ft_putstr_right(ft_itoa(file->bytes), width->bytes);
		ft_putchar(' ');
		ll_file_datetime(&file->mtime);
		ft_putchar(' ');
		ft_putstr(file->name);
		if (file->type == 'l')
		{
			ft_putstr(" -> ");
			linkname = malloc(10000 + 1);
			if (linkname == NULL)
				exit(EXIT_FAILURE);
			r = readlink(file->path, linkname, 10000 + 1); // À corriger !!!!
			if (r < 0)
				exit(EXIT_FAILURE);

			if (r > 10000)
				exit(EXIT_FAILURE);
			linkname[10000] = '\0';
			ft_putstr(linkname);
		}
		ft_putchar('\n');
		file = file ->next;
	}
}
