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

#ifndef FDF_H
# define FDF_H

# include <mlx.h>
# include "libft/libft.h"

# define WIN_X 1500
# define WIN_Y 1000

typedef struct			s_fract
{
	char				type;
	float				minX;
	float				maxX;
	float				minY;
	float				maxY;
	t_bool				wait;
	void				*win;
	void				*mlx;
	void				*img;
	char				*imgstr;
	float				julia_val;
	float				julia_vali;
}						t_fract;

#endif
