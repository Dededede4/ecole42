/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gnebie <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/27 04:13:46 by gnebie            #+#    #+#             */
/*   Updated: 2017/03/27 14:42:34 by ntoniolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_H
# define STRUCT_H

/*
** Structures
*/

typedef struct		s_draw
{
	int				x;
	int				y;
	int				max;
	int				count;
	int				cur_champ;
	int				save_pros;
	int				highlight;
}					t_draw;

typedef struct		s_cycle
{
	int				cycle;
	int				total_cycle;
	int				cycle_to_die;
	int				check;
}					t_cycle;

typedef struct		s_op
{
	const char		*name;
	int				nb_arg;
	int				tab_arg[3];
	int				op_code;
	int				cycle;
	const char		*doc;
	int				have_ocp;
	int				nbr_octet_dir;
}					t_op;

typedef struct		s_champ
{
	char			champ[CHAMP_MAX_SIZE];
	char			champ_name[PROG_NAME_LENGTH + 1];
	char			champ_com[COMMENT_LENGTH + 1];
	char			voider;
	int				champ_nbr;
	int				champ_size;
	int				champ_position;
}					t_champ;

typedef struct		s_process
{
	int					reg[REG_NUMBER + 1];
	int					in_stock[4];
	int					instruc;
	struct s_process	*next;
	int					pc;
	int					cycle;
	char				carry;
	char				live;
	char				instruction;
	char				champion;
	int					voider2;
	long int			nb;
}					t_process;

typedef struct		s_lives
{
	long			total_lives;
	long			cycle_lives;
	long			champ_total_lives[MAX_PLAYERS];
	long			champ_cycle_lives[MAX_PLAYERS];
	int				last_live;
	int				cycle_last_live;
}					t_lives;

typedef struct		s_ncurses
{
	WINDOW			*win;
	WINDOW			*inf;
	int				key;
	int				size_max_y;
	int				size_max_x;
	int				cur_pros;
	int				cur_menu;
	int				i_print;
	int				wall_cycle;
	int				i_com;
	int				sort_cycle;
	char			str_com[NC_COM_LEN];
	int				len_com;
	unsigned char	background[MEM_SIZE];
	unsigned char	light[MEM_SIZE];
	struct timeval	t1;
	struct timeval	t2;
}					t_nc;

typedef struct		s_inf
{
	long			nbr_process;
	long			total_lives;
	long			cycle_lives;
	long			cycle_last_live;
	int				champion;
	int				cur_process;
}					t_inf;

typedef struct		s_datas
{
	t_process		*begin_process;
	t_champ			*begin_champ;
	t_lives			*lives;
	t_cycle			cycle;
	t_nc			nc;
	t_op			op_tab[40];
	t_inf			inf[5];
	int				player_nbr;
	int				nbr_cycles;
	int				start[4];
	int				flag;
	int				dump;
	long int		nb_process;
	int				i_debug;
	int				end;
	char			arene[MEM_SIZE];
	int				pid[3];
}					t_datas;

#endif
