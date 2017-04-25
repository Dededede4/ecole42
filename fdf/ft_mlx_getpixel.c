/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mlx_getpixel.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mprevot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/24 12:51:10 by mprevot           #+#    #+#             */
/*   Updated: 2017/04/24 12:51:11 by mprevot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

t_pixel	ft_mlx_getpixel(size_t x, size_t y)
{
	t_pixel val;

	val.x = x;
	val.y = y;
	val.c = 0xfffff;
	return (val);
}

t_position ft_mlx_getposition(size_t x, size_t y, size_t z)
{
	t_position val;

	val.x = x;
	val.y = y;
	val.z = z;
	val.c = 0xfffff;
	return (val);
}

t_position *ft_mlx_mallocposition(size_t x, size_t y, size_t z)
{
	t_position *val;

	val = ft_memalloc(sizeof(t_position));
	val->x = x;
	val->y = y;
	val->z = z;
	val->c = 0xfffff;
	return (val);
}