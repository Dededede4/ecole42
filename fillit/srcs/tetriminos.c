/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   creat_tetriminos.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmasiala <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/07 13:14:30 by fmasiala          #+#    #+#             */
/*   Updated: 2016/12/07 14:42:19 by mprevot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fillit.h"

t_tetri	*ft_tetrinew(char *tetri, int pos, char c)
{
	t_tetri	*new;

	new = (t_tetri *)malloc(sizeof(t_tetri));
	if (new == NULL)
		return (NULL);
	new->c = c;
	new->d = NULL;
	new->l = NULL;
	new->r = NULL;
	new->t = NULL;
	new->printed = 0;
	tetri[pos] = 'X';
	if (pos + 5 < 21 && tetri[pos + 5] == '#')
		new->d = ft_tetrinew(tetri, pos + 5, c);
	if (pos - 1 >= 0 && tetri[pos - 1] == '#')
		new->l = ft_tetrinew(tetri, pos - 1, c);
	if (pos + 1 < 21 && tetri[pos + 1] == '#')
		new->r = ft_tetrinew(tetri, pos + 1, c);
	return (new);
}

void	ft_print_tetriminos(t_tetri *t)
{
	char	*map;

	map = ft_newmap(9);
	ft_write_tetriminos(map, 9, t, 5);
	ft_putstr(map);
}

t_tetri	**ft_creat_tetriminos(char *path, int nbr)
{
	t_tetri	**tetris;
	int		i;
	int		fd;
	int		check;
	char	*str;

	i = 0;
	check = 0;
	fd = ft_open(path);
	str = ft_strnew(21);
	tetris = malloc(nbr * sizeof(t_tetri));
	while ((check = read(fd, str, 21)) >= 20)
	{
		tetris[i] = ft_tetrinew(ft_strchr(str, '#'), 0, 'A' + i);
		i++;
	}
	close(fd);
	free(str);
	return (tetris);
}
