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

void	draw_square(t_map *map, int pos, int w)
{
	int i;
	int i2;
	int bs;

	bs = w * 4;
	i = 0;
	pos -= pos % 4;
	while (i < w)
	{
		i2 = 0;
		while (i2 < bs)
		{
			map->imgstr[pos + i2] = (unsigned char)MINIMAP_COLOR;
			map->imgstr[pos + i2 + 1] = (unsigned char)MINIMAP_COLOR;
			map->imgstr[pos + i2 + 2] = (unsigned char)MINIMAP_COLOR;
			i2+=4;
		}
		pos += (WIN_X * 4);
		i++;
	}
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
	if ((y * MAP_W + x) >= MAP_SIZE || (y * MAP_W + x) < 0)
		return FALSE;
	return (map->mapstr[y * MAP_W + x] == MAP_BLOCK);
}

float		deg_to_rad(float deg)
{
	return (deg * (3.14159265 / 180));
}



void	print_wall_col(t_map *map, int x, int pixels_wall, char o)
{
	int top;
	int i;

	i = 1;
	if (WIN_Y < pixels_wall)
		pixels_wall = WIN_Y;
	top = ((((WIN_Y - pixels_wall) / 2) * WIN_X) * 4);
	while (i < pixels_wall)
	{
		map->imgstr[(x * 4) + (top)] = (unsigned char)255 / o;
		map->imgstr[(x * 4) + (top) + 1] = (unsigned char)255 / o;
		map->imgstr[(x * 4) + (top) + 2] = (unsigned char)255 / o;
		map->imgstr[(x * 4) + (top) + 3] = (unsigned char)0;
		top+=WIN_X * 4;
		i++;
	}
	
}

void	print_wall(t_map *map, int pixel)
{
	float deg;
	float wall_dist;
	float size;
	int degint;
	char o;

	deg = (WIN_X - pixel) * (VIEW_DEG / (float)WIN_X) + (map->user_deg - 30);
	degint = (int)deg % 360;
	deg = degint + (deg - (int)deg);
	if (deg < 0)
		deg = 360 + deg;
	wall_dist = get_wall_distance(map, deg, &o);
	size = (WIN_Y / (float)WALL_DIV) / wall_dist;
	print_wall_col(map, pixel, size, o);
}

void	compute_map(t_map *map)
{
	memset_horizon(map);
	for (int i = 0; i < FRAME_LIMIT; ++i)
	{
		print_wall(map, i);
	}
	memset_minimap(map);
	memset_minimap_user(map);
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
	mlx_loop(map->mlx);
	return (0);
}

