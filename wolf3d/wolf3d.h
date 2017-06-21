/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wolf3d.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mprevot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/10 14:17:48 by mprevot           #+#    #+#             */
/*   Updated: 2017/06/10 14:17:50 by mprevot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WOLF3D_H
# define WOLF3D_H

# include <mlx.h>
# include "libft/libft.h"

# define WIN_X 800
# define WIN_Y 450

# define MAP_SIZE 144
# define MAP_W 12
# define MAP_BLOCK	'#'
# define MAP_START	'*'
# define MAP_STOP	'S'
# define MAP_EMPTY	'.'

# define MINIMAP_X 50
# define MINIMAP_Y 100
# define MINIMAP_BLOCK_SIZE 20
# define MINIMAP_USER_SIZE  3
# define MINIMAP_COLOR 100

# define VIEW_DEG 60
# define WALL_DIV 3

# define FRAME_LIMIT WIN_X

# define NORTH 1
# define SOUTH 2
# define EAST 3
# define WEST 4


typedef struct			s_map
{
	void				*win;
	void				*mlx;
	void				*img;
	char				*imgstr;
	int					imgstrlen;
	char				mapstr[MAP_SIZE + 1];
	float				user_posx;
	float				user_posy;
	int					user_deg;
}						t_map;

typedef struct			s_pixel
{
	int				x;
	int				y;
}						t_pixel;

float		get_wall(t_map *map, float deg);
float		deg_to_rad(float deg);
t_bool		is_wall(t_map *map, int x, int y);

void	memset_horizon(t_map *map);
void	memset_minimap(t_map *map);
void	memset_minimap_user(t_map *map);
void	hydrate_map(char *str, t_map *map);
t_map		*get_map(void);
int			on_key_press(int keycode, t_map *map);
void		display_map(t_map *map);
void				on_key_press_126(t_map *map);
void				on_key_press_125(t_map *map);
void				on_key_press_37(t_map *map);
void				on_key_press_41(t_map *map);
void				on_key_press_123(t_map *map);
void				on_key_press_124(t_map *map);
void	draw_square(t_map *map, int pos, int w);
void	compute_map(t_map *map);
#endif
