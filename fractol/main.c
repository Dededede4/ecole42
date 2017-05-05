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
#include <stdio.h>


void		draw_mandelbrot(t_fract *fract)
{
	float rc;
	float ic;
	float r;
	float rz;
	float iz;
	int		a;
	int y2;
	int x2;
	t_tmp_pixel	*first;
	t_tmp_pixel	*current;

	first = NULL;
	ft_bzero(fract->imgstr, WIN_X * WIN_Y * 4);
	for (int x = 0; x < 1499; x += 1)
	{
		for (int y = 0; y < 999; y += 1)
		{
			rc = (fract->type != 2) ? fract->minX + (fract->maxX - fract->minX) / WIN_X * x : fract->julia_val;
			ic = (fract->type != 2) ? fract->minY + (fract->maxY - fract->minY) / WIN_Y * y : fract->julia_vali;
			rz = (fract->type == 2) ? fract->minX + (fract->maxX - fract->minX) / WIN_X * x : 0;
			iz = (fract->type == 2) ? fract->minY + (fract->maxY - fract->minY) / WIN_Y * y : 0;
			for (a = 0; a < 127; ++a)
			{
				r = rz;
				rz = r * r - iz * iz + rc;
				iz = 2 * iz * r + ic;
				if (fract->type == 3 )
				{
					x2 = ((rz - fract->minX) * (WIN_X / ((fract->maxX - fract->minX))));
					y2 = ((iz - fract->minY) * (WIN_Y / (fract->maxY - fract->minY)));
					if (x2 > 0 && y2 > 0 && y2 < WIN_Y && x2 < WIN_X)
					{
						current = ft_memalloc(sizeof(t_tmp_pixel));
						current->x = x2;
						current->y = y2;
						if (!first)
							first = current;
						else
						{
							current->next = first;
							first = current;
						}
					}
				}

				if (rz * rz + iz * iz >= 4)
					break;
			}
			if (fract->type == 3 )
			{
				current = first;
				if (a < 127)
				{
					
					while(current)
					{
						if ((unsigned char)fract->imgstr[(current->y * WIN_X * 4) + (current->x*4)] < 255)
						{
							fract->imgstr[(current->y * WIN_X * 4) + (current->x*4)] += 10;
							fract->imgstr[(current->y * WIN_X * 4) + (current->x*4) + 1] += 10;
							fract->imgstr[(current->y * WIN_X * 4) + (current->x*4) + 2] += 10;
						}
							current = current->next;
					}
					
					
				}
				while (first)
					{
						current = first->next;
						free(first);
						first = current;
					}
			}
			else
			{
				a *= 2;
				fract->imgstr[(y * WIN_X * 4) + (x*4)] = a;
				fract->imgstr[(y * WIN_X * 4) + (x*4) + 1] = a;
				fract->imgstr[(y * WIN_X * 4) + (x*4) + 2] = a;
			}
		}
	}
	mlx_put_image_to_window(fract->imgstr, fract->win, fract->img, 0, 0);

}

int				on_mouse_move(int button,int x,int y,t_fract *fract)
{
	if (button == 7 || button == 4)
	{
		float x_s = fract->maxX - fract->minX;
		float rx = x_s * x / WIN_X;
		float toaddX = rx - ((fract->maxX - fract->minX) / 2);

		float y_s = fract->maxY - fract->minY;
		float ry = y_s * y / WIN_Y;
		float toaddY = ry - ((fract->maxY - fract->minY) / 2);

		fract->minY += toaddY;
		fract->maxY += toaddY;
		fract->minX += toaddX;
		fract->maxX += toaddX;

		fract->minY *= 0.9;
		fract->minX *= 0.9;
		fract->maxY *= 0.9;
		fract->maxX *= 0.9;
	}
	if (button == 5) // up
	{
		fract->minY *= 1.1;
		fract->maxY *= 1.1;
		fract->minX *= 1.1;
		fract->maxX *= 1.1;
	}
	draw_mandelbrot(fract);
	return (1);
}

int 		motion_hook(int x,int y, t_fract *fract)
{
	if (x < 0 || x > WIN_X || y < 0 || y > WIN_Y || fract->type != 2)
		return (0);
	fract->julia_val = 0 - ((((float)x / WIN_X)));
	draw_mandelbrot(fract);
	return (1);
}

int				main(int argc, char **argv)
{
	t_fract		fract;
	int			bpp;
	int			s_l;
	int			endian;

	if (argc != 2)
	{
		ft_putstr_fd("Usage : ./fractol [1-3]", STDERR_FILENO);
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
		ft_putstr_fd("Usage : ./fractol [1-3]", STDERR_FILENO);
		exit(0);
	}
	fract.mlx = mlx_init();
	fract.win = mlx_new_window(fract.mlx, WIN_X, WIN_Y, "Coucou mon coco");
	fract.minX = -2.4;
	fract.maxX = 2.4;
	fract.minY = -1.5;
	fract.maxY = 1.5;
	fract.img = mlx_new_image(fract.mlx, WIN_X, WIN_Y);
	fract.imgstr = mlx_get_data_addr(fract.img, &(bpp), &(s_l), &(endian));
	fract.wait = FALSE;
	fract.julia_val = -0.76;
	fract.julia_vali = 0.12;
	draw_mandelbrot(&fract);
	mlx_mouse_hook(fract.win, on_mouse_move, &fract);
	mlx_hook(fract.win, 6, 0, motion_hook, &fract);
	mlx_loop(fract.mlx);
	exit(0);
}
