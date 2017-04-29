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

int				on_key_press(int keycode, void *param)
{
	(void)(param);
	if (keycode == 53)
		exit(0);
	return (1);
}

void		draw_mandelbrot(float minX, float maxX, float minY, float maxY, void *win, void *mlx)
{
	float rc;
	float ic;
	float r;
	float i;
	float rz;
	float iz;
	int		a;
	int			bpp;
	int			s_l;
	int			endian;
	char*		my_image_string;
	void*		pointeur_img;

	pointeur_img = mlx_new_image(mlx, 1500, 1000);
	my_image_string = mlx_get_data_addr(pointeur_img, &(bpp), &(s_l), &(endian));
	for (int x = 0; x < 1499; ++x)
	{
		for (int y = 0; y < 999; ++y)
		{
			rc = minX + (maxX - minX) / 1500 * x;
			ic = minY + (maxY - minY)/ 1000 * y;
			rz = 0;
			iz = 0;
			for (a = 0; a < 127; ++a)
			{
				r = rz;
				i = iz;
				rz = r * r - i * i + rc;
				iz = 2 * r * i + ic;
				if (rz * rz + iz * iz >= 4)
					break;
			}
			a *= 2;
			my_image_string[(y * 1500 * 4) + (x*4)] = a;
			my_image_string[(y * 1500 * 4) + (x*4) + 1] = a;
			my_image_string[(y * 1500 * 4) + (x*4) + 2] = a;
		}
	}
	mlx_put_image_to_window(my_image_string, win, pointeur_img, 0, 0);

}


int				main(int argc, char **argv)
{

	void		*mlx;
	void		*win;
	

	mlx = mlx_init();
	win = mlx_new_window(mlx, 1500, 1000, "Coucou mon coco");
	draw_mandelbrot(-2.4, 2.4, -1.5, 1.5, win, mlx);
	mlx_loop(mlx);
	exit(0);
}
