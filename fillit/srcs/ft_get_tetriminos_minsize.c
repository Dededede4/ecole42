/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_tetriminos_minsize.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mprevot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/07 14:42:47 by mprevot           #+#    #+#             */
/*   Updated: 2016/12/07 14:42:57 by mprevot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fillit.h"

// TODO tests
int	ft_can_merge_tetriminos(char *map, int width, t_tetri *tetri, int pos)
{
	int		can;

	if (map[pos] == '#' || map[pos] == '\n')
		return (0);
	can = 1;
	if (tetri->r)
	{
		can = ft_can_merge_tetriminos(map, width, tetri->r, pos + 1);
	}
	if (can && tetri->l)
	{
		if (pos == 0)
			return (0);
		can = ft_can_merge_tetriminos(map, width, tetri->l, pos - 1);
	}
	if (can && tetri->d)
	{
		can = ft_can_merge_tetriminos(map, width, tetri->d, pos + width);
	}
	if (can && tetri->t)
	{
		if (pos < width)
			return (0);
		can = ft_can_merge_tetriminos(map, width, tetri->d, pos - width);
	}
	if (can)
		return (1);
	else
		return (0);
}

// TODO tests
void	ft_merge_tetriminos(char *map, int width, t_tetri *tetri, int pos)
{
	map[pos] = '#';
	if (tetri->r)
		ft_merge_tetriminos(map, width, tetri->r, pos + 1);
	if (tetri->l)
		ft_merge_tetriminos(map, width, tetri->l, pos - 1);
	if (tetri->d)
		ft_merge_tetriminos(map, width, tetri->d, pos + width);
	if (tetri->t)
		ft_merge_tetriminos(map, width, tetri->d, pos - width);
}


// TODO tests
int	ft_merge_all_tetriminos(char *map, int width, t_tetri **tetris, int nbr_tetri)
{
	int	i;
	int	y;
	int		goods;
	
	nbr_tetri = 2;
	i = 0;
	goods = 0;
	while (map[i])
	{
		y = 0;
		while (tetris[y])
		{
			if (ft_can_merge_tetriminos(map, width, tetris[i], y))
			{
				ft_merge_tetriminos(map, width, tetris[i], y);
				goods++;
			}
			y++;
		}
		if (goods == nbr_tetri)
			return (1);
		else
			i++;
	}
	return (0);
}

// TODO tests
int	ft_tests_tetriminos_position(char *map, int width, t_tetri **tetris, int nbr_tetri)
{
	int	i;
	char	*map2;
	int	r;
	int	nbr_permutes;

	i = 0;
	nbr_permutes = 0;
	while(i < nbr_tetri)
	{
		map2 = ft_strdup(map);
		r = ft_merge_all_tetriminos(map2, width, tetris, nbr_tetri);
		if (r)
		{

			ft_strcpy(map, map2);
			ft_strclr(map2);
			return (1);
		}
		else
		{
			ft_strclr(map2);
		}
		if (i == nbr_tetri - 1)
		{
			i = 0;
			nbr_permutes++;
		}
		ft_permute((void**)(tetris + nbr_permutes), nbr_tetri - nbr_permutes);
	}
	return (0);
}

// TODO tests
void	ft_permute(void	**str, int len)
{
	void	*last;
	int	i;

	i = len - 2;
	last = str[len - 1];
	while (i)
	{
		str[i + 1] = str[i];
		i--;
	}
	str[1] = str[0];
	str[0] = last;
}


// TODO tests
void	*ft_getmap(int width)
{
	char	*new;
	int 	i;
	int	len;

	i = 0;
	len = (width + 1) * width;
	new = ft_strnew(len);
	if (!new)
		return (NULL);
	while (i < len)
	{
		if (i % width == 0)
			new[i] = '\n';
		else
			new[i] = '.';
	}
	return (new);
}


int		main(int argc, char *argv[])
{
	char	*map;
	int	width;
	int		nbr_tetri;
	t_tetri **tetris;

	nbr_tetri = 0;
	width = 1;
	tetris = reader(argc, argv, &nbr_tetri);
	while (1)
	{
		map = ft_getmap(width);
		if (!map)
			return (0);

		if (ft_tests_tetriminos_position(map, width, tetris, nbr_tetri))
		{
			ft_putstr(map);
			return (0);
		}
		ft_strclr(map);
		width++;
	}
}
