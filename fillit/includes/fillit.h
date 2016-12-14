/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fillit.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmasiala <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/12 15:46:32 by fmasiala          #+#    #+#             */
/*   Updated: 2016/12/14 14:23:59 by mprevot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FILLIT_H
# define FILLIT_H

# include "./libft/libft.h"
# include <string.h>
# include <errno.h>
# include <stdio.h>

typedef struct		s_tetri
{
	struct s_tetri	*l;
	struct s_tetri	*r;
	struct s_tetri	*d;
	struct s_tetri	*t;
	char			c;
	char			printed;
}					t_tetri;

typedef struct		s_params
{
	char			*map;
	int				width;
	int				len;
	t_tetri			**tetris;
	int				nbr_tetri;
}					t_params;

int					ft_open(char *path);
t_tetri				**ft_creat_tetriminos(char *path, int nbr);
t_tetri				**ft_reader(int argc, char *path, int *len);
void				*ft_newmap(int width);
int					ft_check_syntax(char *str);
int					ft_resolve(t_params p,
		int map_pos, int tetri_check);
int					ft_can_write_tetri(t_params p,
		t_tetri *tetri, int pos);
void				ft_write_tetri(char *map, int width,
		t_tetri *tetri, int pos);
void				ft_erase_tetri(char *map, int width,
		t_tetri *tetri, int pos);
#endif
