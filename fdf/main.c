/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mprevot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/26 12:15:39 by mprevot           #+#    #+#             */
/*   Updated: 2017/04/26 12:15:41 by mprevot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int				on_key_press(int keycode, void *param)
{
	(void)(param);
	if (keycode == 53)
		exit(0);
	return (1);
}

void			draw_all_positions(
	void *mlx, void *win, t_position **positions, int width)
{
	int i;
	int len;

	len = 0;
	while (positions[len])
		len++;
	i = 0;
	while (positions[i] && positions[i + 1])
	{
		if ((i + 1) % width != 0)
			ft_mlx_3draw(mlx, win, *(positions[i]), *(positions[i + 1]));
		if (i + width < len)
			ft_mlx_3draw(mlx, win, *(positions[i]), *(positions[i + width]));
		i++;
	}
}

int				main(int argc, char **argv)
{
	void		*mlx;
	void		*win;
	int			width;
	int			len;
	t_position	**positions;

	if (argc != 2)
		ft_error("Usage : ./fdf file.fdf\n");
	len = check_validity(argv[1], &width);
	positions = parsing(argv[1], len, width);
	mlx = mlx_init();
	win = mlx_new_window(mlx, 1000, 1000, "Coucou mon coco");
	draw_all_positions(mlx, win, positions, width);
	mlx_key_hook(win, on_key_press, NULL);
	mlx_loop(mlx);
	exit(0);
}
