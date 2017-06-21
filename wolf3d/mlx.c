/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mprevot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/21 21:51:51 by mprevot           #+#    #+#             */
/*   Updated: 2017/06/21 21:51:53 by mprevot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

t_map		*get_map(void)
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
	return (map);
}

int			on_key_press(int keycode, t_map *map)
{
	if (keycode == 53)
		exit(0);
	if (keycode == 126)
		on_key_press_126(map);
	if (keycode == 125)
		on_key_press_125(map);
	if (keycode == 37)
		on_key_press_37(map);
	if (keycode == 41)
		on_key_press_41(map);
	if (keycode == 123)
		on_key_press_123(map);
	if (keycode == 124)
		on_key_press_124(map);
	map->user_deg = map->user_deg % 360;
	compute_map(map);
	display_map(map);
	return (1);
}

void		display_map(t_map *map)
{
	mlx_put_image_to_window(map->imgstr, map->win, map->img, 0, 0);
}
