/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_okp_1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mprevot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/21 22:10:40 by mprevot           #+#    #+#             */
/*   Updated: 2017/06/21 22:10:42 by mprevot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void				on_key_press_124(t_map *map)
{
	map->user_posx += 0.2;
	if (is_wall(map, map->user_posx, map->user_posy))
		map->user_posx -= 0.2;
	else
		map->user_posx -= 0.1;
}
