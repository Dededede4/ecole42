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

int		ft_resolve(char *map, int width,
		t_tetri **tetris, int nbr_tetri, int tetri_pos, int tetri_check)
{
	int	i;

	i = 0;
	if (tetri_check == nbr_tetri)
		return (1);

	if (tetri_pos == nbr_tetri)
		return (0);

	while (map[i])
	{
		if (tetris[tetri_pos]->printed != 1 && ft_can_write_tetriminos(map, width, tetris[tetri_pos], i))
		{
			tetri_check++;
			ft_write_tetriminos(map, width, tetris[tetri_pos], i);
			tetris[tetri_pos]->printed = 1;
			if (ft_resolve(map, width, tetris, nbr_tetri, tetri_pos + 1, tetri_check) == 1)
			{
				return (1);
			}
			else
			{
				tetris[tetri_pos]->printed = 0;
				tetri_check--;
				ft_erase_tetriminos(map, width, tetris[tetri_pos], i);
			}
		}
		i++;
	}		
	return (ft_resolve(map, width, tetris, nbr_tetri, tetri_pos + 1, tetri_check));
}


