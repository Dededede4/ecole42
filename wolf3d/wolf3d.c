/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wolf3d.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mprevot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/10 14:19:40 by mprevot           #+#    #+#             */
/*   Updated: 2017/06/10 14:19:42 by mprevot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void	draw_square(t_map *map, int pos)
{
	int i;
	int i2;
	int bs;

	bs = MINIMAP_BLOCK_SIZE * 4;
	i = 0;
	while (i < MINIMAP_BLOCK_SIZE)
	{
		i2 = 0;
		while (i2 < bs)
		{
			map->imgstr[pos + i2] = (unsigned char)MINIMAP_COLOR;
			i2++;
		}
		pos += (WIN_X * 4);
		i++;
	}
}

void	memset_horizon(t_map *map)
{
	int i;
	int middle = map->imgstrlen / 2;

	ft_printf("%d\n", map->imgstrlen);
	i = 0;
	while (i < map->imgstrlen)
	{
		if (i < middle)
		{//87ceeb	
			map->imgstr[i + 0] = 0xEB; // Bleu
			map->imgstr[i + 1] = 0xCE;// vert 
			map->imgstr[i + 2] = 0x87; // rouge
		}
		else
		{
			map->imgstr[i + 0] = 0x23;
			map->imgstr[i + 1] = 0x9D;
			map->imgstr[i + 2] = 0x3A;
		}
		i += 4;
	}
}

void	memset_minimap(t_map *map)
{
	int current = ((MINIMAP_X) + (WIN_X * MINIMAP_Y)) * 4;
	int start;
	int i;
	int y;
	int map_pos;

	ft_printf("%s\n", map->mapstr);
	map_pos = 0;
	i = 0;
	while (i < MAP_W)
	{
		start = current;
		y = 0;
		while (y < MAP_W)
		{
			if (map->mapstr[map_pos++] == MAP_BLOCK)
				draw_square(map, current);
			current += MINIMAP_BLOCK_SIZE * 4;
			y++;
		}
		current = start + (WIN_X * MINIMAP_BLOCK_SIZE * 4);
		i++;
	}
}

t_map	*get_map()
{
	t_map	*map;
	int		bpp;
	int		s_l;
	int		endian;

	map = ft_memalloc(sizeof(t_map));
	map->mlx = mlx_init();
	map->win = mlx_new_window(map->mlx, WIN_X, WIN_Y, "Coucou mon coco");
	map->img = mlx_new_image(map->mlx, WIN_X, WIN_Y);
	map->imgstr = mlx_get_data_addr(map->img, &(bpp), &(s_l), &(endian));
	map->imgstrlen = WIN_X * WIN_Y * 4;
	return map;
}

void	display_map(t_map *map)
{
	mlx_put_image_to_window(map->imgstr, map->win, map->img, 0, 0);
	mlx_loop(map->mlx);
}

void	compute_map(t_map *map)
{
	memset_horizon(map);
	memset_minimap(map);
}

void	hydrate_map(char *str, t_map *map)
{
	int 	fd;
	char	*line;
	int 	i;
	int 	chars;
	int     test_square;

	(void)map;
	i = -1;
	chars = 0;
	line = NULL;
	fd = open(str, O_RDONLY);
	test_square = -1;
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
		ft_printf("%s\n", map->mapstr);
	}
	if (chars != MAP_SIZE)
	{
		ft_printf("Bad map size\n");
		exit(0);
	}
	ft_printf("%s\n", map->mapstr);
}

int main(int argc, char **argv)
{
	t_map	*map;

	if (argc != 2)
	{
		ft_printf("Usage : ./wolf3d labyrinthe.map\n");
		exit(0);
	}
	map = get_map();
	hydrate_map(argv[1], map);
	compute_map(map);
	display_map(map);
	return (0);
}