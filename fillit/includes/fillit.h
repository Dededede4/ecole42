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

int					ft_strlinelen(char *s);
int					ft_open(char *path);
t_tetri				**ft_creat_tetriminos(char *path, int nbr);
void				ft_permute(void	**str, int len, int start);
t_tetri				**ft_reader(int argc, char *path, int *len);
void				*ft_newmap(int width);
int					ft_tetri_checker(int check, char *str);
int					ft_error(int argc);
int					ft_count_cara(char *str);
void				ft_permete_to_first(void **mem, int pos);
int					ft_resolve(char *map, int width,
		t_tetri **tetris, int nbr_tetri, int map_pos, int tetri_check);
void				ft_write_tetriminos(char *map, int width,
		t_tetri *tetri, int pos);
int					ft_sqrt(int nb);
int					ft_check_end_file(int check, int last);
int					ft_empty_map(char *map);
int					ft_can_write_tetriminos(char *map, int width, t_tetri *tetri, int pos);
void				ft_write_tetriminos(char *map, int width, t_tetri *tetri, int pos);
void				ft_erase_tetriminos(char *map, int width, t_tetri *tetri, int pos);
#endif
