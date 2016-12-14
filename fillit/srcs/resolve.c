/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_tetriminos_minsize.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mprevot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/07 14:42:47 by mprevot           #+#    #+#             */
/*   Updated: 2016/12/09 15:03:11 by mprevot          ###   ########.fr       */
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
			ft_can_write_tetriminos(p.map, p.width, p.tetris[tetri_pos], i))
		{
			tetri_check++;
			ft_write_tetriminos(p.map, p.width, p.tetris[tetri_pos], i);
			p.tetris[tetri_pos]->printed = 1;
			if (ft_resolve(p, tetri_pos + 1, tetri_check) == 1)
			{
				return (1);
			}
			else
			{
				p.tetris[tetri_pos]->printed = 0;
				tetri_check--;
				ft_erase_tetriminos(p.map, p.width, p.tetris[tetri_pos], i);
			}
		}
		i++;
	}
	return (ft_resolve(p, tetri_pos + 1, tetri_check));
}
