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

int			ft_abs(int val)
{
	return ((val < 0) ? 0 - val : val);
}

void		ft_mlx_draw_put_a(void *mlx, void *win, t_pixel start, t_pixel stop)
{
	int		len_x;
	int		s_len_x;
	int		d_len_y;
	int		i;

	i = 0;
	len_x = ft_abs(stop.x - start.x);
	s_len_x = len_x;
	d_len_y = 2 * ft_abs(stop.y - start.y);
	while (i <= s_len_x)
	{
		mlx_pixel_put(mlx, win, start.x, start.y, (int)start.c);
		i++;
		start.x += (start.x > stop.x) ? -1 : 1;
		len_x -= d_len_y;
		if (len_x < 0)
		{
			start.y += (start.y > stop.y) ? -1 : 1;
			len_x += 2 * s_len_x;
		}
	}
}

void		ft_mlx_draw_put_b(void *mlx, void *win, t_pixel start, t_pixel stop)
{
	int		len_y;
	int		s_len_y;
	int		d_len_x;
	int		i;

	i = 0;
	len_y = ft_abs(stop.y - start.y);
	s_len_y = len_y;
	d_len_x = 2 * ft_abs(stop.x - start.x);
	while (i <= s_len_y)
	{
		mlx_pixel_put(mlx, win, start.x, start.y, (int)start.c);
		i++;
		start.y += (start.y > stop.y) ? -1 : 1;
		len_y -= d_len_x;
		if (len_y < 0)
		{
			start.x += (start.x > stop.x) ? -1 : 1;
			len_y += 2 * s_len_y;
		}
	}
}

void		ft_mlx_draw(void *mlx, void *win, t_pixel start, t_pixel stop)
{
	int		len_x;
	int		len_y;

	len_x = ft_abs(stop.x - start.x);
	len_y = ft_abs(stop.y - start.y);
	if (len_x >= len_y)
	{
		ft_mlx_draw_put_a(mlx, win, start, stop);
	}
	else
	{
		ft_mlx_draw_put_b(mlx, win, start, stop);
	}
}

void		ft_mlx_3draw(
	void *mlx, void *win, t_position start, t_position stop)
{
	t_pixel a;
	t_pixel b;

	a = ft_mlx_getpixel(ft_abs(start.y + start.x),
		ft_abs(start.x - start.y - start.z));
	b = ft_mlx_getpixel(ft_abs(stop.y + stop.x),
		ft_abs(stop.x - stop.y - stop.z));
	ft_mlx_draw(mlx, win, a, b);
}
