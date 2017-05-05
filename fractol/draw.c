/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mprevot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/05 11:56:17 by mprevot           #+#    #+#             */
/*   Updated: 2017/05/05 11:56:18 by mprevot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void				draw_calcpoint(
	t_fract *fract, t_fract_cals *vars)
{
	vars->rc = (fract->type != 2) ?
		fract->minx + (fract->maxx - fract->minx) / WIN_X * vars->x
		: fract->julia_val;
	vars->ic = (fract->type != 2) ?
		fract->miny + (fract->maxy - fract->miny) / WIN_Y * vars->y
		: fract->julia_vali;
	vars->rz = (fract->type == 2) ?
		fract->minx + (fract->maxx - fract->minx) / WIN_X * vars->x
		: 0;
	vars->iz = (fract->type == 2) ?
		fract->miny + (fract->maxy - fract->miny) / WIN_Y * vars->y
		: 0;
}

void				draw_calcpoint_intern(
	t_fract *fract, t_fract_cals *vars,
	t_tmp_pixel **first, t_tmp_pixel *current)
{
	vars->r = vars->rz;
	vars->rz = vars->r * vars->r - vars->iz * vars->iz + vars->rc;
	vars->iz = 2 * vars->iz * vars->r + vars->ic;
	if (fract->type == 3)
	{
		vars->x2 = ((vars->rz - fract->minx) * (WIN_X /
			((fract->maxx - fract->minx))));
		vars->y2 = ((vars->iz - fract->miny) * (WIN_Y /
			(fract->maxy - fract->miny)));
		if (vars->x2 > 0 && vars->y2 > 0 && vars->y2 < WIN_Y
			&& vars->x2 < WIN_X)
		{
			current = ft_memalloc(sizeof(t_tmp_pixel));
			current->x = vars->x2;
			current->y = vars->y2;
			if (!*first)
				*first = current;
			else
			{
				current->next = *first;
				*first = current;
			}
		}
	}
}

void				draw_after_type3(
		t_fract *fract, t_fract_cals *vars,
		t_tmp_pixel **first, t_tmp_pixel *current)
{
	current = *first;
	if (vars->a < 127)
	{
		while (current)
		{
			if ((unsigned char)fract->imgstr[(current->y * WIN_X * 4)
				+ (current->x * 4)] < 255)
			{
				fract->imgstr[(current->y * WIN_X * 4)
				+ (current->x * 4)] += 10;
				fract->imgstr[(current->y * WIN_X * 4)
				+ (current->x * 4) + 1] += 10;
				fract->imgstr[(current->y * WIN_X * 4)
				+ (current->x * 4) + 2] += 10;
			}
			current = current->next;
		}
	}
	while (*first)
	{
		current = (*first)->next;
		free(*first);
		*first = current;
	}
}

void				draw_for(
	t_fract *fract, t_fract_cals *vars,
	t_tmp_pixel *first, t_tmp_pixel *current)
{
	draw_calcpoint(fract, vars);
	vars->a = 0;
	while (vars->a < 127)
	{
		vars->a++;
		draw_calcpoint_intern(fract, vars, &first, current);
		if (vars->rz * vars->rz + vars->iz * vars->iz >= 4)
			break ;
	}
	if (fract->type == 3)
		draw_after_type3(fract, vars, &first, current);
	else
	{
		vars->a *= 2;
		fract->imgstr[(vars->y * WIN_X * 4) + (vars->x * 4)] = vars->a;
		fract->imgstr[(vars->y * WIN_X * 4) + (vars->x * 4) + 1] = vars->a;
		fract->imgstr[(vars->y * WIN_X * 4) + (vars->x * 4) + 2] = vars->a;
	}
}

void				draw(t_fract *fract)
{
	t_fract_cals	vars;
	t_tmp_pixel		*first;
	t_tmp_pixel		*current;

	first = NULL;
	current = NULL;
	ft_bzero(fract->imgstr, WIN_X * WIN_Y * 4);
	vars.x = 0;
	while (vars.x < 1499)
	{
		vars.x++;
		vars.y = 0;
		while (vars.y < 999)
		{
			vars.y++;
			draw_for(fract, &vars, first, current);
		}
	}
	mlx_put_image_to_window(fract->imgstr, fract->win, fract->img, 0, 0);
}
