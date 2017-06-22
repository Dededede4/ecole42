/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_wall_distance.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mprevot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/21 23:15:14 by mprevot           #+#    #+#             */
/*   Updated: 2017/06/21 23:15:16 by mprevot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"
#include <math.h>

float		deg_to_rad(float deg)
{
	return (deg * (3.14159265 / 180));
}

/*
**           * A
**          **
**         * *
**        *  *
**     C * * * B
** c = player
*/

float		get_wall_distance_x(t_map *map, float deg, float realdeg, char *o)
{
	t_walldist v;

	v.repeat = 0;
	while (v.repeat < 15)
	{
		v.c_b = (realdeg < 90 || realdeg > 270) ?
			(((int)map->user_posx + 1) - map->user_posx) + v.repeat :
			(map->user_posx - ((int)map->user_posx)) + v.repeat;
		v.a_c = v.c_b / cos(deg_to_rad(deg));
		v.a_b = v.c_b * tan(deg_to_rad(deg));
		v.x = (realdeg < 90 || realdeg > 270) ?
			map->user_posx + v.c_b : map->user_posx - v.c_b - 1;
		v.y = (realdeg < 180) ?
			map->user_posy - v.a_b : map->user_posy + v.a_b;
		if (is_wall(map, v.x, v.y))
		{
			*o = (v.x < map->user_posx) ? EAST : WEST;
			return (v.a_c);
		}
		v.repeat++;
	}
	return (-1);
}

float		get_wall_distance_y(t_map *map, float deg, float realdeg, char *o)
{
	t_walldist v;

	v.repeat = 0;
	while (v.repeat < 15)
	{
		v.c_b = (realdeg < 180) ?
			(map->user_posy - ((int)map->user_posy)) + v.repeat :
			(((int)map->user_posy + 1) - map->user_posy) + v.repeat;
		v.a_c = v.c_b / cos(deg_to_rad(deg));
		v.a_b = v.c_b * tan(deg_to_rad(deg));
		v.x = (realdeg < 90 || realdeg > 270) ?
			map->user_posx + v.a_b : map->user_posx - v.a_b;
		v.y = (realdeg < 180) ?
			map->user_posy - v.c_b - 1 : map->user_posy + v.c_b;
		if (is_wall(map, v.x, v.y))
		{
			*o = (v.y < map->user_posy) ? NORTH : SOUTH;
			return (v.a_c);
		}
		v.repeat++;
	}
	return (-1);
}

float		get_wall_distance(t_map *map, float realdeg, char *orientation)
{
	float	hypo_x;
	float	hypo_y;
	char	orientation_x;
	char	orientation_y;
	float	deg;

	if (realdeg < 90)
		deg = realdeg;
	else if (realdeg < 180)
		deg = 180 - realdeg;
	else if (realdeg < 270)
		deg = realdeg - 180;
	else
		deg = 360 - realdeg;
	hypo_x = get_wall_distance_x(map, deg, realdeg, &orientation_x);
	deg = 90 - deg;
	hypo_y = get_wall_distance_y(map, deg, realdeg, &orientation_y);
	if (hypo_y < 0 || (hypo_y >= hypo_x && hypo_x > 0))
	{
		*orientation = orientation_x;
		return (hypo_x);
	}
	*orientation = orientation_y;
	return (hypo_y);
}
