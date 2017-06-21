/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mprevot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/21 22:12:45 by mprevot           #+#    #+#             */
/*   Updated: 2017/06/21 22:12:48 by mprevot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void		puterr(char *str)
{
	ft_printf(str);
	exit(0);
}

int			hydrate_map_gnl_check(t_map *map, char *line, int *chars, int *y)
{
	int		i;

	i = 0;
	while (line[i])
	{
		if (line[i] != MAP_BLOCK && line[i] != MAP_START &&
			line[i] != MAP_STOP && line[i] != MAP_EMPTY)
			puterr("Unknow char\n");
		if (line[i] == MAP_START)
		{
			map->user_posx = i + 0.5;
			map->user_posy = *y + 0.5;
		}
		if (*chars > MAP_SIZE)
			puterr("Too much chars\n");
		map->mapstr[(*chars)++] = line[i];
		i++;
	}
	return (i);
}

int			hydrate_map_gnl(t_map *map, int fd)
{
	char	*line;
	int		chars;
	int		test_square;
	int		y;
	int		i;

	line = NULL;
	chars = 0;
	test_square = -1;
	y = 0;
	while (ft_gnl(fd, &line))
	{
		i = hydrate_map_gnl_check(map, line, &chars, &y);
		if (test_square != -1 && test_square != i)
			puterr("Not a sqare\n");
		test_square = i;
		y++;
	}
	return (chars);
}

void		hydrate_map(char *str, t_map *map)
{
	int		fd;
	int		chars;

	fd = open(str, O_RDONLY);
	map->user_deg = 90;
	if (fd < 1)
		puterr("File error\n");
	chars = hydrate_map_gnl(map, fd);
	if (chars != MAP_SIZE)
		puterr("Bad map size\n");
}
