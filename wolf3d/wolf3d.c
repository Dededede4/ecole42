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
#include <math.h>
#include <stdio.h>

void	draw_square(t_map *map, int pos, int w)
{
	int i;
	int i2;
	int bs;

	bs = w * 4;
	i = 0;
	while (i < w)
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
				draw_square(map, current, MINIMAP_BLOCK_SIZE);
			current += MINIMAP_BLOCK_SIZE * 4;
			y++;
		}
		current = start + (WIN_X * MINIMAP_BLOCK_SIZE * 4);
		i++;
	}
}

void	memset_minimap_user(t_map *map)
{
	int pos;

	pos = ((MINIMAP_X) + (WIN_X * MINIMAP_Y)) * 4;
	pos += ((map->user_posx * MINIMAP_BLOCK_SIZE) + (map->user_posy * MINIMAP_BLOCK_SIZE * WIN_X)) * 4;

	draw_square(map, pos, MINIMAP_USER_SIZE);
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
}

void	compute_map(t_map *map)
{
	memset_horizon(map);
	memset_minimap(map);
	memset_minimap_user(map);
}

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
		ft_printf("%s\n", map->mapstr);
		y++;
	}
	if (chars != MAP_SIZE)
	{
		ft_printf("Bad map size\n");
		exit(0);
	}
	ft_printf("%s\n", map->mapstr);
}

int					on_key_press(int keycode, t_map *map)
{
	(void)(map);
	if (keycode == 53)
		exit(0);
	if (keycode == 126) // up
	{
		map->user_posy -= 0.1;
	}
	if (keycode == 125) // down
	{
		map->user_posy += 0.1;
	}
	if (keycode == 123) // left
	{
		map->user_posx -= 0.1;
	}
	if (keycode == 124) // right
	{
		map->user_posx += 0.1;
	}
	compute_map(map);
	display_map(map);
	ft_printf("%d", keycode);
	return (1);
}

/**
**           * A
**          **
**         * *
**        *  *
**     C * * * B
** c = player
**/

t_bool		is_wall(t_map *map, int x, int y)
{
	return (map->mapstr[y * MAP_W + x] == MAP_BLOCK);
}

float		deg_to_rad(float deg)
{
	return (deg * (3.14159265 / 180));
}

float		get_wall(t_map *map, float deg)
{
	int repeat;
	float c_b;
	float a_d;
	float a_e;
	float a_c;
	float a_b;
	//float deg = 60; // On peut monter jusqu'à moins de 90deg
	int x;
	int y;
	float hypo;

	repeat = 0;
	hypo = 0;

	while (1)
	{
		c_b = (((int)map->user_posx + 1) - map->user_posx) + repeat;
		//printf("cb = %f\n", c_b);
		//printf("%f\n", deg_to_rad(deg));
		//printf("%f\n", cos(deg_to_rad(deg)));
		a_c = c_b / cos(deg_to_rad(deg)); // = hypothenuse
		//printf("%f %f\n", cos(60), cos(60.0) );
		//printf("%f / cos(%f) = %f\n", c_b, deg, c_b / cos(deg));
		//printf("ac = %f\n", a_c);
		a_b = c_b * tan(deg_to_rad(deg)); // = opposé
		//printf("a_b = %f\n", a_b);
		hypo += a_c;
		x = map->user_posx + c_b;
		y = map->user_posy - a_b;
		if (is_wall(map, x, y))
		{
			a_e = hypo - ((int)hypo);
			a_d = a_e * a_c / a_b;
			return hypo - a_d;
		}
		repeat++;
	}
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
	mlx_key_hook(map->win, on_key_press, map);
	for (int i = 60; i < 90; ++i)
	{
		printf("%ddeg = %f\n\n", i, get_wall(map, i));
		//exit(0);
	}
	
	mlx_loop(map->mlx);
	return (0);
}