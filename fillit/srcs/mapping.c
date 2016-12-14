/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mapping.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mprevot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/14 15:04:55 by mprevot           #+#    #+#             */
/*   Updated: 2016/12/14 15:04:58 by mprevot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fillit.h"

void	*ft_newmap(int width)
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
	if (can)
		return (1);
	else
		return (0);
}

void	ft_write_tetriminos(char *map, int width, t_tetri *tetri, int pos)
{
	map[pos] = tetri->c;
	tetri->printed = 1;
	if (tetri->r)
		ft_write_tetriminos(map, width, tetri->r, pos + 1);
	if (tetri->l)
		ft_write_tetriminos(map, width, tetri->l, pos - 1);
	if (tetri->d)
		ft_write_tetriminos(map, width, tetri->d, pos + width + 1);
}

void	ft_erase_tetriminos(char *map, int width, t_tetri *tetri, int pos)
{
	map[pos] = '.';
	tetri->printed = 0;
	if (tetri->r)
		ft_erase_tetriminos(map, width, tetri->r, pos + 1);
	if (tetri->l)
		ft_erase_tetriminos(map, width, tetri->l, pos - 1);
	if (tetri->d)
		ft_erase_tetriminos(map, width, tetri->d, pos + width + 1);
}
