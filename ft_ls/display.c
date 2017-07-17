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

void	ll_file_datetime(const time_t *clock)
{
	char	*str;
	char	**split;

	str = ctime(clock);
	split = ft_strsplit(str, ' ');
	if (*clock > time(NULL) - (3600 * 24 * 30 * 6) && *clock <= time(NULL))
		ft_printf("%3s %2s %.5s", split[1], split[2], split[3]);
	else
	{
		if (ft_atoi(split[4]) >= 10000)
			ft_printf("%3s %2s %6d", split[1], split[2], ft_atoi(split[4]));
		else
			ft_printf("%3s %2s %5d", split[1], split[2], ft_atoi(split[4]));
	}
}

void	long_display_while(t_file *file, t_width *width, t_params *params)
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
	file = file->next;
}

void	long_display(t_path *pcur, t_file *file, t_params *params)
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
