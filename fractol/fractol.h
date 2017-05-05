/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mprevot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/29 18:25:24 by mprevot           #+#    #+#             */
/*   Updated: 2017/04/29 18:25:26 by mprevot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_H
# define FRACTOL_H

# include <mlx.h>
# include "libft/libft.h"

# define WIN_X 1500
# define WIN_Y 1000

typedef struct			s_fract
{
	char				type;
	float				minx;
	float				maxx;
	float				miny;
	float				maxy;
	t_bool				wait;
	void				*win;
	void				*mlx;
	void				*img;
	char				*imgstr;
	float				julia_val;
	float				julia_vali;
}						t_fract;

typedef struct			s_fract_cals
{
	float				rc;
	float				ic;
	float				r;
	float				rz;
	float				iz;
	int					a;
	int					x;
	int					y;
	int					y2;
	int					x2;
}						t_fract_cals;

typedef struct			s_tmp_pixel
{
	size_t				x;
	size_t				y;
	struct s_tmp_pixel	*next;
}						t_tmp_pixel;

void					draw(t_fract *fract);

#endif
