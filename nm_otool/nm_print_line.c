/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_line.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mprevot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/15 03:24:38 by mprevot           #+#    #+#             */
/*   Updated: 2018/12/15 03:24:52 by mprevot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm.h"

t_bool	can_show_next(t_line *line, t_line *findme)
{
	while (line)
	{
		if (0 == ft_strcmp(line->right, findme->right)
			&& line->middle == findme->middle
			&& (line->left == findme->left || !line->left || !findme->left))
		{
			return (FALSE);
		}
		line = line->next;
	}
	return (TRUE);
}

t_bool	can_show(t_line *first, t_line *findme)
{
	t_line	*line;
	int		i;

	i = 0;
	line = first;
	if (0 == ft_strlen(findme->right) ||
		findme->middle == '?' || findme->middle == '-')
		return (FALSE);
	while (line)
	{
		if (0 == ft_strcmp(line->right, findme->right)
			&& line->middle == findme->middle
			&& (line->left == findme->left || !line->left || !findme->left))
		{
			if (line == findme)
				return (TRUE);
			line = line->next;
			break ;
		}
		line = line->next;
	}
	return (can_show_next(line, findme));
}

void	print_line(t_line *line)
{
	t_line *first;

	first = line;
	while (line)
	{
		if (can_show(first, line))
		{
			if (line->is_64)
			{
				if (line->left || line->middle == 'T')
					ft_printf("%016llx ", line->left);
				else
					ft_printf("                 ");
			}
			if (line->is_32)
			{
				if (line->left || line->middle == 'T')
					ft_printf("%08llx ", line->left);
				else
					ft_printf("         ");
			}
			ft_printf("%C %s\n", line->middle, line->right);
		}
		line = line->next;
	}
}
