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

int		ft_can_write_tetri(t_params p, t_tetri *tetri, int pos)
{
	int		can;

	if (p.map[pos] != '.')
		return (0);
	can = 1;
	if (tetri->r)
	{
		can = 0;
		if (pos + 1 < p.len)
			can = ft_can_write_tetri(p, tetri->r, pos + 1);
	}
	if (can && tetri->l)
	{
		if (pos == 0)
			return (0);
		can = 0;
		if (pos - 1 < p.len)
			can = ft_can_write_tetri(p, tetri->l, pos - 1);
	}
	if (can && tetri->d)
	{
		can = 0;
		if (pos + p.width + 1 < p.len)
			can = ft_can_write_tetri(p, tetri->d, pos + p.width + 1);
	}
	return (can);
}

void	ft_write_tetri(char *map, int width, t_tetri *tetri, int pos)
{
	map[pos] = tetri->c;
	tetri->printed = 1;
	if (tetri->r)
		ft_write_tetri(map, width, tetri->r, pos + 1);
	if (tetri->l)
		ft_write_tetri(map, width, tetri->l, pos - 1);
	if (tetri->d)
		ft_write_tetri(map, width, tetri->d, pos + width + 1);
}

void	ft_erase_tetri(char *map, int width, t_tetri *tetri, int pos)
{
	map[pos] = '.';
	tetri->printed = 0;
	if (tetri->r)
		ft_erase_tetri(map, width, tetri->r, pos + 1);
	if (tetri->l)
		ft_erase_tetri(map, width, tetri->l, pos - 1);
	if (tetri->d)
		ft_erase_tetri(map, width, tetri->d, pos + width + 1);
}
