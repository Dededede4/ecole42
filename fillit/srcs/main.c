/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmasiala <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/09 09:18:18 by fmasiala          #+#    #+#             */
/*   Updated: 2016/12/13 11:56:33 by fmasiala         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fillit.h"

int				main(int argc, char **argv)
{
	t_params	p;
	t_tetri		**tetris;

	p.nbr_tetri = 0;
	p.width = 2;
	tetris = ft_reader(argc, argv[1], &p.nbr_tetri);
	while (1)
	{
		p.map = ft_newmap(p.width);
		p.len = (p.width + 1) * p.width + 1;
		if (!p.map)
			return (0);
		if (ft_resolve(p, 0, 0))
		{
			ft_putstr(p.map);
			return (0);
		}
		ft_strclr(p.map);
		p.width++;
	}
	return (1);
}
