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

	//ft_printf("%d\n", map->imgstrlen);
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

	//ft_printf("%s\n", map->mapstr);
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
	printf("%d\n", pos);
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
		//ft_printf("%s\n", map->mapstr);
		y++;
	}
	if (chars != MAP_SIZE)
	{
		ft_printf("Bad map size\n");
		exit(0);
	}
	//ft_printf("%s\n", map->mapstr);
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

float		get_wall_0_90(t_map *map, float realdeg)
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
	float hypo_x;
	float hypo_y;

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
	//printf("-->%f\n", realdeg);
	//printf("-->%f\n", deg);
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
		//ft_printf("is_wall ? %d %d;\n", x, y);
		if (is_wall(map, x, y))
		{
			//printf("Check des x %d %d %f (%f:%f) -> %f %f %f\n", x, y, a_c, deg, realdeg, c_b, a_b, a_c);
			hypo_x = a_c;
			break;
		}
		repeat++;
	}

	repeat = 0;
	// Check des y
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
			//printf("c_b -> %f pos -> %f result -> %f\n", c_b, map->user_posy, map->user_posy - c_b);

		}
		else
		{
			y = map->user_posy + c_b;
		}
		//ft_printf("is_wall ? %d %d;\n", x, y);
		if (is_wall(map, x, y))
		{
			//printf("Check des y %d %d %f (%f:%f) -> %f %f %f\n", x, y, a_c, deg, realdeg, c_b, a_b, a_c);
			hypo_y = a_c;
=======
	hypo_x = -1;
	hypo_y = -1;


	while (repeat < 15)
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
		x = map->user_posx + c_b;
		y = map->user_posy - a_b;
		if (is_wall(map, x, y))
		{
			hypo_x = a_c;
			break;
		}
		repeat++;
	}

	repeat = 0;
	deg = 90 - deg;

	while (repeat < 15)
	{
		c_b = (((int)map->user_posy + 1) - map->user_posy) + repeat;
		//printf("cb = %f\n", c_b);
		//printf("%f\n", deg_to_rad(deg));
		//printf("%f\n", cos(deg_to_rad(deg)));
		a_c = c_b / cos(deg_to_rad(deg)); // = hypothenuse
		//printf("%f %f\n", cos(60), cos(60.0) );
		//printf("%f / cos(%f) = %f\n", c_b, deg, c_b / cos(deg));
		//printf("ac = %f\n", a_c);
		a_b = c_b * tan(deg_to_rad(deg)); // = opposé
		//printf("a_b = %f\n", a_b);
		x = map->user_posx + a_b;
		y = map->user_posy - a_c;
		//printf("%d %d\n", x, y);
		if (is_wall(map, x, y))
		{
			hypo_y = a_c;
			break;
		}
		repeat++;
	}

>>>>>>> d7d86b8b11f8203385393f4054c88581c99fc4a3
	if (hypo_y < 0)
		return (hypo_x);
	if (hypo_x < 0)
		return (hypo_y);
	return ((hypo_y < hypo_x) ? hypo_y : hypo_x);
}

void	print_wall_col(t_map *map, int x, int pixels_wall)
{
	int top;
	int i;
	int stop = WIN_Y * 4;

	//printf("====>%d\n", x);
	i = 1;
	if (WIN_Y < pixels_wall)
		pixels_wall = WIN_Y;
	top = ((((WIN_Y - pixels_wall) / 2) * WIN_X) * 4);
	//printf("top = %d\n", top);
	while (i < pixels_wall)
	{
		//printf("%d\n", (x * 4) + top);
		map->imgstr[(x * 4) + (top)] = (unsigned char)255;
		map->imgstr[(x * 4) + (top) + 1] = (unsigned char)255;
		map->imgstr[(x * 4) + (top) + 2] = (unsigned char)255;
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

	deg = (WIN_X - pixel) * (VIEW_DEG / (float)WIN_X) + (map->user_deg - 30); //user deg
	degint = (deg);
	degint = degint % 360;
	deg = degint + (deg - (int)deg);
	if (deg < 0)
		deg = 360 + deg;
	printf("%f\n", deg);
	wall_dist = get_wall_0_90(map, deg);
	//printf("olala->%f\n", wall_dist);
	size = (WIN_Y / (float)WALL_DIV) / wall_dist;
	print_wall_col(map, pixel, size);
	// size du pixel WIN_X - pixel =

}

void	compute_map(t_map *map)
{
	memset_horizon(map);
	for (int i = 1; i < FRAME_LIMIT; ++i)
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
	ft_printf("%d", keycode);
	return (1);
}


int main(int argc, char **argv)
{
	t_map	*map;
	float	testval;

	if (argc != 2)
	{
		ft_printf("Usage : ./wolf3d labyrinthe.map\n");
		exit(0);
	}

	map = get_map();
	
	if (ft_strcmp(argv[1], "test") == 0)
	{
		//printf("hey\n");
		hydrate_map("labyrinthe.map", map);
		//printf("%f %f\n", map->user_posx, map->user_posy);
		/*map->user_posx = 5.67;
		map->user_posy = 10.79;*/
		/*
		map->user_posx = 5.70;
		map->user_posy = 10.80;*/

		for (int i = 90; i < 120; i += 5)
		{
			if (i != 90)
			{
				testval = get_wall_0_90(map, (float)i);
				//printf("%i = %f\n", i, testval);
				printf("%f\n", testval);
			}
			
		}
		exit(0);
		compute_map(map);
		display_map(map);
		//mlx_loop(map->mlx);
		exit(0);
	}
	else
	{
		hydrate_map(argv[1], map);	
		compute_map(map);
		display_map(map);
	}
	//printf("%ddeg = %f\n\n", 75, get_wall_0_90(map, 75));
	/* for (int i = 1; i < 180; i += 10)
	{
		if (i != 90)
			printf("%ddeg = %f\n\n", i, get_wall_0_90(map, i));
		//printf("%ddeg = %f\n\n", i, get_wall_90_180(map, i));
	}*/
	
	mlx_key_hook(map->win, on_key_press, map);
	mlx_loop(map->mlx);
	return (0);
}

