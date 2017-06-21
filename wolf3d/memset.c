/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memset.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mprevot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/21 21:49:23 by mprevot           #+#    #+#             */
/*   Updated: 2017/06/21 21:49:27 by mprevot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void	memset_horizon(t_map *map)
{
	int i;
	int middle;

	middle = map->imgstrlen / 2;
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
	int current;
	int start;
	int i;
	int y;
	int map_pos;

	current = ((MINIMAP_X) + (WIN_X * MINIMAP_Y)) * 4;
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
	pos += ((map->user_posx * MINIMAP_BLOCK_SIZE)
		+ (map->user_posy * MINIMAP_BLOCK_SIZE * WIN_X)) * 4;
	draw_square(map, pos, MINIMAP_USER_SIZE);
}
