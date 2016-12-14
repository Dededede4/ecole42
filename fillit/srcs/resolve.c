/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   resolve.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mprevot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/14 17:06:46 by mprevot           #+#    #+#             */
/*   Updated: 2016/12/14 17:06:55 by mprevot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fillit.h"

int		ft_resolve(t_params p, int tetri_pos, int tetri_check)
{
	int	i;

	i = 0;
	if (tetri_check == p.nbr_tetri)
		return (1);
	if (tetri_pos == p.nbr_tetri)
		return (0);
	while (p.map[i])
	{
		if (p.tetris[tetri_pos]->printed != 1 &&
			ft_can_write_tetri(p, p.tetris[tetri_pos], i))
		{
			tetri_check++;
			ft_write_tetri(p.map, p.width, p.tetris[tetri_pos], i);
			if (ft_resolve(p, tetri_pos + 1, tetri_check) == 1)
				return (1);
			else
			{
				tetri_check--;
				ft_erase_tetri(p.map, p.width, p.tetris[tetri_pos], i);
			}
		}
		i++;
	}
	return (ft_resolve(p, tetri_pos + 1, tetri_check));
}
