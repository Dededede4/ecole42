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

int		ft_can_merge_tetriminos(char *map, int width, t_tetri *tetri, int pos)
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
			can = ft_can_merge_tetriminos(map, width, tetri->r, pos + 1);
		else
			can = 0;
	}
	if (can && tetri->l)
	{
		if (pos == 0)
			return (0);
		if (pos - 1 < len)
			can = ft_can_merge_tetriminos(map, width, tetri->l, pos - 1);
		else
			can = 0;
	}
	if (can && tetri->d)
	{
		if (pos + width + 1 < len)
			can = ft_can_merge_tetriminos(map, width, tetri->d,
					pos + width + 1);
		else
			can = 0;
	}
	/*if (can && tetri->t)
	  {
	  if (pos < width)
	  return (0);
	  can = ft_can_merge_tetriminos(map, width, tetri->d, pos - width - 1);
	  }*/
	if (can)
		return (1);
	else
		return (0);
}

// TODO tests

void	ft_merge_tetriminos(char *map, int width, t_tetri *tetri, int pos)
{
	map[pos] = tetri->c;
	if (tetri->r)
		ft_merge_tetriminos(map, width, tetri->r, pos + 1);
	if (tetri->l)
		ft_merge_tetriminos(map, width, tetri->l, pos - 1);
	if (tetri->d)
		ft_merge_tetriminos(map, width, tetri->d, pos + width + 1);
	if (tetri->t)
		ft_merge_tetriminos(map, width, tetri->d, pos - width - 1);
}

// TODO tests

int		ft_merge_all_tetriminos(char *map, int width, t_tetri **tetris,
		int nbr_tetri)
{
	int		i;
	int		y;
	int		goods;

	i = 0;
	goods = 0;
	while (map[i])
	{
		y = 0;
		while (y < nbr_tetri)
		{
			if (!tetris[y]->printed &&
					ft_can_merge_tetriminos(map, width, tetris[y], i))
			{
				ft_merge_tetriminos(map, width, tetris[y], i);
				tetris[y]->printed = 1;
				goods++;
			}
			y++;
		}
		if (goods == nbr_tetri)
			return (1);
		i++;
	}
	return (0);
}

// TODO tests

int		ft_tests_tetriminos_position(char *map, int width,
		t_tetri **tetris, int nbr_tetri)
{
	int		i;
	char	*map2;
	int		r;
	int		nbr_all_permutes;
	int		big_permutes;

	i = 0;
	nbr_all_permutes = 0;
	big_permutes = 0;
	while (big_permutes < nbr_tetri)
	{
		while (i + nbr_all_permutes <= nbr_tetri)
		{
			map2 = ft_strdup(map);
			r = ft_merge_all_tetriminos(map2, width, tetris, nbr_tetri);
			if (r)
			{
				ft_strcpy(map, map2);
				return (1);
			}
			ft_strclr(map2);
			if (i + nbr_all_permutes == nbr_tetri)
			{
				ft_putstr("permuteee\n");
				i = 0;
				//ft_permute((void**)tetris, nbr_tetri, nbr_all_permutes);
				nbr_all_permutes++;
			}
			ft_permute((void**)tetris, nbr_tetri, nbr_all_permutes);
			i++;
		}
		ft_putstr("**************\n");
		big_permutes++;
		i = 0;
		nbr_all_permutes = 1;
		if (big_permutes > 1)
			ft_permete_to_first((void**)tetris, big_permutes - 1);
		ft_permete_to_first((void**)tetris, big_permutes);
	}
	return (0);
}

// TODO tests

void    ft_permete_to_first(void **mem, int pos)
{
	void	*first;

	first = mem[0];
	mem[0] = mem[pos];
	mem[pos] = first;
}

void	ft_permute(void **mem, int len, int start)
{
	void	*last;
	int		i;

	if (len - start <= 0)
		return ;
	i = 0;
	while (i < len)
	{
		ft_putchar(((t_tetri**)mem)[i]->c);
		i++;
	}
	ft_putchar('\n');

	i = len - 1;
	last = mem[i];
	while (i > start)
	{
		mem[i] = mem[i - 1];
		i--;
	}
	mem[start] = last;
}

// TODO tests

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
