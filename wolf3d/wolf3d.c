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

float		get_wall_0_90(t_map *map, float realdeg, char *orientation)
{
	int repeat;
	float c_b;
	float a_c;
	float a_b;
	int x;
	int y;
	float hypo_x;
	float hypo_y;
	char orientation_x;
	char orientation_y;

	repeat = 0;
	hypo_x = -1;
	hypo_y = -1;
	float deg;

	if (realdeg < 90)
		deg = realdeg;
	else if (realdeg < 180)
		deg = 180 - realdeg;
	else if (realdeg < 270)
		deg = realdeg - 180;
	else
		deg = 360 - realdeg;
	while (repeat < 15)
	{
		if (realdeg < 90 || realdeg > 270)
			c_b = (((int)map->user_posx + 1) - map->user_posx) + repeat;
		else
			c_b = (map->user_posx - ((int)map->user_posx)) + repeat;

		a_c = c_b / cos(deg_to_rad(deg));
		a_b = c_b * tan(deg_to_rad(deg));

		if (realdeg < 90 || realdeg > 270)
		{
			x = map->user_posx + c_b;
		}
		else
		{
			x = map->user_posx - c_b;
			x--;
		}

		if (realdeg < 180)
		{
			y = map->user_posy - a_b;
		}
		else
		{
			y = map->user_posy + a_b;
		}
		if (is_wall(map, x, y))
		{
			orientation_x = (x < map->user_posx) ? EAST : WEST;
			hypo_x = a_c;
			break;
		}
		repeat++;
	}

	repeat = 0;
	deg = 90 - deg;
	while (repeat < 15)
	{
		if (realdeg < 180)
			c_b = (map->user_posy - ((int)map->user_posy)) + repeat;
		else
			c_b = (((int)map->user_posy + 1) - map->user_posy) + repeat;
		a_c = c_b / cos(deg_to_rad(deg));
		a_b = c_b * tan(deg_to_rad(deg));
		if (realdeg < 90 || realdeg > 270)
		{
			x = map->user_posx + a_b;
		}
		else
		{
			x = map->user_posx - a_b;
		}

		if (realdeg < 180)
		{
			y = map->user_posy - c_b;
			y--;
		}
		else
		{
			y = map->user_posy + c_b;
		}
		if (is_wall(map, x, y))
		{
			orientation_y = (y < map->user_posy) ? NORTH : SOUTH;
			hypo_y = a_c;
			break;
		}
		repeat++;
	}

	if (hypo_y < 0)
	{
		*orientation = orientation_x;
		return (hypo_x);
	}
	if (hypo_x < 0)
	{
		*orientation = orientation_y;
		return (hypo_y);
	}
	if (hypo_y < hypo_x){
		*orientation = orientation_y;
		return hypo_y;
	}
	else
	{
		*orientation = orientation_x;
		return hypo_x;
	}
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
	wall_dist = get_wall_0_90(map, deg, &o);
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

