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

void	hydrate_map(char *str, t_map *map)
{
	int 	fd;
	char	*line;
	int 	i;
	int 	chars;
	int     test_square;
	int     y;

	(void)map;
	i = -1;
	chars = 0;
	line = NULL;
	fd = open(str, O_RDONLY);
	test_square = -1;
	map->user_deg = 90;
	y = 0;
	if (fd < 1)
	{
		ft_printf("File error\n");
		exit(0);
	}
	while (ft_gnl(fd, &line))
	{
		i = 0;
		while (line[i])
		{
			if (line[i] != MAP_BLOCK && line[i] != MAP_START &&  line[i] != MAP_STOP &&  line[i] != MAP_EMPTY)
			{
				ft_printf("Unknow char\n");
				exit(0);
			}
			if (line[i] == MAP_START)
			{
				map->user_posx = i + 0.5;
				map->user_posy = y + 0.5;
			}
			if (chars > MAP_SIZE)
			{
				ft_printf("Too much chars\n");
				exit(0);
			}
			map->mapstr[chars++] = line[i];
			i++;
		}
		if (test_square != -1 && test_square != i)
		{
			ft_printf("Not a sqare\n");
			exit(0);
		}
		test_square = i;
		y++;
	}
	if (chars != MAP_SIZE)
	{
		ft_printf("Bad map size\n");
		exit(0);
	}
}
