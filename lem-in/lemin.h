/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lemin.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mprevot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/17 11:59:16 by mprevot           #+#    #+#             */
/*   Updated: 2017/02/17 11:59:18 by mprevot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEMIN_H
# define LEMIN_H

# include "libft/libft.h"

# define START 1
# define END 2
# define FREE 3
# define IGNORE 4
# define OCCUPY 5

typedef char			t_status;

typedef struct			s_antler
{
	size_t				ant_nbr_global;
	size_t				ant_nbr_start;
	char				*input;
	struct s_pipe		*pipes;
	struct s_room		*rooms;
	struct s_room		*start;
	struct s_room		*end;
}						t_antler;

typedef struct			s_room
{
	char				*name;
	int					x;
	int					y;
	int					ant_no;
	t_bool				have_way;
	struct s_room		*next;
}						t_room;

typedef struct s_list	t_way;
typedef struct s_list	t_ways;
typedef struct s_list	t_ant;

typedef struct			s_pipe
{
	struct s_room		*a;
	struct s_room		*b;
	struct s_pipe		*next;
}						t_pipe;

t_antler				*lemin_parser(void);
void					lemin_output(t_antler	*antler);
void					error(void);
t_ways					*find_sortest_ways(t_antler *antler);
void					freelst(t_way **ways);
t_bool					isended(t_way *way);
t_bool					send_ants(t_antler *antler,
							t_ways	*ways, int *last_no);
t_bool					ft_printmoves_positives(t_way *way);
t_bool					ft_printmoves_negatives(t_way *way);
t_room					*newroom(t_antler *antler,
							t_bool is_start, t_bool is_end);
t_antler				*newantler(void);
t_bool					is_free(t_room *room, t_way *way);
t_bool					usedway(t_way *way);
t_room					*ft_findroom(char	*name, t_antler *antler);
char					*ft_room2str(t_room *room);
char					*ft_pipe2str(t_pipe *pipe);
#endif
