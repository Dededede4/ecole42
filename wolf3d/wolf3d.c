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

void		compute_map(t_map *map)
{
	int		i;

	i = 0;
	memset_horizon(map);
	while (i < FRAME_LIMIT)
	{
		print_wall(map, i);
		i++;
	}
	memset_minimap(map);
	memset_minimap_user(map);
}

int			main(int argc, char **argv)
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
