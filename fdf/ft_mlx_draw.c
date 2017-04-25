/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mlx_draw.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mprevot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/24 12:49:53 by mprevot           #+#    #+#             */
/*   Updated: 2017/04/24 12:49:55 by mprevot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int		ft_abs(int val)
{
	return ((val < 0) ? 0 - val : val);
}

void	ft_mlx_draw(void *mlx, void *win, t_pixel start, t_pixel stop)
{
	int ex = ft_abs(stop.x - start.x);
	int ey = ft_abs(stop.y - start.y);
	int dx = 2 * ex;
	int dy = 2 * ey;
	int Dx = ex;
	int Dy = ey;
	int i = 0;
	int Xincr = 1;
	int Yincr = 1;

	if (start.x > stop.x)
		Xincr = -1;
	if (start.y > stop.y)
		Yincr = -1;
	if (Dx >= Dy)
	{
		while (i <= Dx)
		{
			mlx_pixel_put(mlx, win, start.x, start.y, (int)start.c);
			i++;
			start.x += Xincr;
			ex -= dy;
			if (ex < 0)
			{
				start.y += Yincr;
				ex += dx;
			}
		}
	}
	if (Dy > Dx)
	{
		while (i <= Dy)
		{
			mlx_pixel_put(mlx, win, start.x, start.y, (int)start.c);
			i++;
			start.y += Yincr;
			ey -= dx;
			if (ey < 0)
			{
				start.x += Xincr;
				ey += dy;
			}
		}
	}
}


void	ft_mlx_3draw(void *mlx, void *win, t_position start, t_position stop)
{
	t_pixel a = ft_mlx_getpixel(ft_abs(start.y + start.x), ft_abs(start.x - start.y - start.z));
	t_pixel b = ft_mlx_getpixel(ft_abs(stop.y + stop.x), ft_abs(stop.x - stop.y - stop.z));

	//ft_printf("%zu %zu\n%zu %zu\n\n", a.x, a.y, b.x, b.y);
	ft_mlx_draw(mlx, win, a, b);
}