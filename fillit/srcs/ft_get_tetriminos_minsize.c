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

// TODO tests

/* Teste si on peut écrire un tetris dans une position */
int		ft_can_write_tetriminos(char *map, int width, t_tetri *tetri, int pos)
{
	int		can;
	int		len;

	len = (width + 1) * width + 1;
	if (map[pos] != '.')
		return (0);
	can = 1;
	if (tetri->r)
	{
		if (pos + 1 < len)
			can = ft_can_write_tetriminos(map, width, tetri->r, pos + 1);
		else
			can = 0;
	}
	if (can && tetri->l)
	{
		if (pos == 0)
			return (0);
		if (pos - 1 < len)
			can = ft_can_write_tetriminos(map, width, tetri->l, pos - 1);
		else
			can = 0;
	}
	if (can && tetri->d)
	{
		if (pos + width + 1 < len)
			can = ft_can_write_tetriminos(map, width, tetri->d,
					pos + width + 1);
		else
			can = 0;
	}
	/*if (can && tetri->t)
	  {
	  if (pos < width)
	  return (0);
	  can = ft_can_write_tetriminos(map, width, tetri->d, pos - width - 1);
	  }*/
	if (can)
		return (1);
	else
		return (0);
}

// TODO tests
/* Écrit un tetri dans une position */
void	ft_write_tetriminos(char *map, int width, t_tetri *tetri, int pos)
{
	map[pos] = tetri->c;
	if (tetri->r)
		ft_write_tetriminos(map, width, tetri->r, pos + 1);
	if (tetri->l)
		ft_write_tetriminos(map, width, tetri->l, pos - 1);
	if (tetri->d)
		ft_write_tetriminos(map, width, tetri->d, pos + width + 1);
	/*if (tetri->t)
		ft_write_tetriminos(map, width, tetri->d, pos - width - 1);*/
}

void	ft_erase_tetriminos(char *map, int width, t_tetri *tetri, int pos)
{
	map[pos] = '.';
	if (tetri->r)
		ft_erase_tetriminos(map, width, tetri->r, pos + 1);
	if (tetri->l)
		ft_erase_tetriminos(map, width, tetri->l, pos - 1);
	if (tetri->d)
		ft_erase_tetriminos(map, width, tetri->d, pos + width + 1);
}

int		ft_write_all_tetriminos(char *map, int width,
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
			if (ft_write_all_tetriminos(map, width, tetris, nbr_tetri, tetri_pos + 1, tetri_check) == 1)
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
	return (ft_write_all_tetriminos(map, width, tetris, nbr_tetri, tetri_pos + 1, tetri_check));
}

void	*ft_getmap(int width)
{
	char	*new;
	int		i;
	int		len;

	i = 0;
	len = (width + 1) * width;
	new = ft_strnew(len);
	if (!new)
		return (NULL);
	while (i < len)
	{
		if (((i + 1) % (width + 1)) == 0)
			new[i] = '\n';
		else
			new[i] = '.';
		i++;
	}
	return (new);
}
