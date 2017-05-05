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

#include "fractol.h"

int					on_mouse_move(int button, int x, int y, t_fract *f)
{
	float			toaddx;
	float			toaddy;

	if (button == 7 || button == 4)
	{
		toaddx = ((f->maxx - f->minx) * x / WIN_X) - ((f->maxx - f->minx) / 2);
		toaddy = (f->maxy - f->miny) * y / WIN_Y - ((f->maxy - f->miny) / 2);
		f->miny += toaddy;
		f->maxy += toaddy;
		f->minx += toaddx;
		f->maxx += toaddx;
		f->miny *= 0.9;
		f->minx *= 0.9;
		f->maxy *= 0.9;
		f->maxx *= 0.9;
	}
	if (button == 5)
	{
		f->miny *= 1.1;
		f->maxy *= 1.1;
		f->minx *= 1.1;
		f->maxx *= 1.1;
	}
	draw(f);
	return (1);
}

int					on_key_press(int keycode, void *param)
{
	(void)(param);
	if (keycode == 53)
		exit(0);
	return (1);
}

int					motion_hook(int x, int y, t_fract *fract)
{
	if (x < 0 || x > WIN_X || y < 0 || y > WIN_Y || fract->type != 2)
		return (0);
	fract->julia_val = 0 - ((((float)x / WIN_X)));
	draw(fract);
	return (1);
}

void				init(t_fract *fract)
{
	int				bpp;
	int				s_l;
	int				endian;

	fract->mlx = mlx_init();
	fract->win = mlx_new_window(fract->mlx, WIN_X, WIN_Y, "Coucou mon coco");
	fract->minx = -2.4;
	fract->maxx = 2.4;
	fract->miny = -1.5;
	fract->maxy = 1.5;
	fract->img = mlx_new_image(fract->mlx, WIN_X, WIN_Y);
	fract->imgstr = mlx_get_data_addr(fract->img, &(bpp), &(s_l), &(endian));
	fract->wait = FALSE;
	fract->julia_val = -0.76;
	fract->julia_vali = 0.12;
}

int					main(int argc, char **argv)
{
	t_fract			fract;

	if (argc != 2)
	{
		ft_putstr_fd("Usage : ./fractol [1-3]\n", STDERR_FILENO);
		exit(0);
	}
	if (ft_strcmp(argv[1], "1") == 0)
		fract.type = 1;
	else if (ft_strcmp(argv[1], "2") == 0)
		fract.type = 2;
	else if (ft_strcmp(argv[1], "3") == 0)
		fract.type = 3;
	else
	{
		ft_putstr_fd("Usage : ./fractol [1-3]\n", STDERR_FILENO);
		exit(0);
	}
	init(&fract);
	mlx_key_hook(fract.win, on_key_press, NULL);
	draw(&fract);
	mlx_mouse_hook(fract.win, on_mouse_move, &fract);
	mlx_hook(fract.win, 6, 0, motion_hook, &fract);
	mlx_loop(fract.mlx);
	exit(0);
}
