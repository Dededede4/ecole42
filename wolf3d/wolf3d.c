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

void	memset_horizon(t_map *map)
{
	int i;
	int middle = map->imgstrlen / 2;

	i = 0;
	while (i < map->imgstrlen)
	{
		if (i < middle)
		{
			map->imgstr[i + 0] = 0xEB;
			map->imgstr[i + 1] = 0xCE;
			map->imgstr[i + 2] = 0x87;
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

int					on_key_press(int keycode, t_map *map)
{
	(void)(map);
	if (keycode == 53)
		exit(0);
	if (keycode == 126) // up
	{
		map->user_posy -= 0.1;
		if (is_wall(map, map->user_posx, map->user_posy))
			map->user_posy += 0.1;
	}
	if (keycode == 125) // down
	{
		map->user_posy += 0.3;
		if (is_wall(map, map->user_posx, map->user_posy))
			map->user_posy -= 0.3;
		else
			map->user_posy -= 0.2;
	}
	if (keycode == 37)
	{
		map->user_deg += 5;
		if (map->user_deg > 360)
			map->user_deg = 5;
	}
	if (keycode == 41)
	{
		map->user_deg -= 5;
		if (map->user_deg < 0)
			map->user_deg = 355;
	}
	if (keycode == 123)
	{
		map->user_posx -= 0.1;
		if (is_wall(map, map->user_posx, map->user_posy))
			map->user_posx += 0.1;
	}
	if (keycode == 124)
	{
		map->user_posx += 0.2;
		if (is_wall(map, map->user_posx, map->user_posy))
			map->user_posx -= 0.2;
		else
			map->user_posx -= 0.1;
	}
	map->user_deg = map->user_deg % 360;
	compute_map(map);
	display_map(map);
	return (1);
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

