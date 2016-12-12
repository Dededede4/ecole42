/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmasiala <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/09 09:18:18 by fmasiala          #+#    #+#             */
/*   Updated: 2016/12/09 15:12:02 by mprevot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fillit.h"

int		main(int argc, char **argv)
{
	char	*map;
	int		width;
	int		nbr_tetri;
	t_tetri **tetris;

	nbr_tetri = 0;
	width = 2;
	while (1)
	{
		tetris = reader(argc, argv[1], &nbr_tetri);
		map = ft_getmap(width);
		ft_putstr("Nouvelle map…\n");
		if (!map)
			return (0);
		if (ft_tests_tetriminos_position(map, width, tetris, nbr_tetri, 0) == 1)
		{
			ft_putstr(map);
			return (0);
		}
		ft_strclr(map);
		width++;
	}
	return (1);
}
