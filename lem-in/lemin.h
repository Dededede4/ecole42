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
	size_t				ant_nbr_end;


	struct s_pipe		*pipes;
	struct s_room		*rooms;
	struct s_room		*start;
	struct s_room		*end;

	struct s_way		*ways;	
}						t_antler;

/*typedef struct			s_way
{
	struct s_room			*start;
	size_t				len;

	struct s_way		*next;
}						t_way;*/

typedef struct			s_room
{
	char				*name;
	int					x;
	int					y;

	t_bool				have_way;
	t_bool				busy;
	
	struct s_room		*next;
}						t_room;

typedef struct s_list	t_wayroom;
typedef struct s_list	t_ways;

typedef struct			s_pipe
{
	struct s_room		*a;
	struct s_room		*b;
	struct s_pipe		*next;
}						t_pipe;


t_antler	*lemin_parser(void);
char	*ft_room2str(t_room *room);
char	*ft_pipe2str(t_pipe *pipe);
t_room	*ft_findroom(char	*name, t_antler *antler);
char	*ft_strjoin_multi(t_bool autofree, ...);
t_bool		ft_isdigit_str(char *str);
void	lemin_output(t_antler	*antler);
void	error(void);
#endif
