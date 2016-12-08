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

t_tetri		*ft_tetrinew(char *tetri, int pos, char c)
{
	t_tetri	*new;

	new = (t_tetri *)malloc(sizeof(t_tetri));
	if (new == NULL)
		return (NULL);
	new->c = c;
	if (tetri[pos + 5] == '#')
		new->d = ft_tetrinew(tetri, pos + 5, c);
	if (tetri[pos + 4] == '#')
		new->l = ft_tetrinew(tetri, pos + 4, c);
	if (tetri[pos + 6] == '#')
		new->r = ft_tetrinew(tetri, pos + 6, c);
	new->t = NULL;
	return (new);
}

t_tetri		**creat_tetriminos(char *argv, int nbr)
{
	t_tetri	**tetris;
	int		i;
	char	c = 'A';
	int		fd;
	int		check;
	char	*str;

	i = 0;
	check = 0;
	fd = ft_open(&argv);
	str = ft_strnew(21);
	tetris = malloc(nbr * sizeof(t_tetri));

	while((check = read(fd, str, 21)) >= 20)
	{

		tetris[i] = ft_tetrinew(ft_strchr(str, '#'), 0, c + i);
		i++;
	}
	close(fd);
	free(str);
	return (tetris);
}
