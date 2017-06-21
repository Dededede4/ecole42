/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_okp_0.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mprevot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/21 22:10:34 by mprevot           #+#    #+#             */
/*   Updated: 2017/06/21 22:10:37 by mprevot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void				on_key_press_126(t_map *map)
{
	map->user_posy -= 0.1;
	if (is_wall(map, map->user_posx, map->user_posy))
		map->user_posy += 0.1;
}

void				on_key_press_125(t_map *map)
{
	map->user_posy += 0.3;
	if (is_wall(map, map->user_posx, map->user_posy))
		map->user_posy -= 0.3;
	else
		map->user_posy -= 0.2;
}

void				on_key_press_37(t_map *map)
{
	map->user_deg += 5;
	if (map->user_deg > 360)
		map->user_deg = 5;
}

void				on_key_press_41(t_map *map)
{
	map->user_deg -= 5;
	if (map->user_deg < 0)
		map->user_deg = 355;
}

void				on_key_press_123(t_map *map)
{
	map->user_posx -= 0.1;
	if (is_wall(map, map->user_posx, map->user_posy))
		map->user_posx += 0.1;
}
