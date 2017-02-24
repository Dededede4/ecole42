/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lemin_parser.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mprevot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/17 11:58:42 by mprevot           #+#    #+#             */
/*   Updated: 2017/02/17 11:58:44 by mprevot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"


void	lemin_parser_antnbr(t_antler *antler)
{
	char	*ant_nbr;

	ft_gnl(STDIN_FILENO, &ant_nbr);
	if (!(ft_isdigit_str(ant_nbr)))
		error();
	antler->ant_nbr_global = ft_atoi(ant_nbr);
	antler->ant_nbr_start = antler->ant_nbr_global;
	antler->ant_nbr_end = antler->ant_nbr_start;
	free(ant_nbr);
}

void	lemin_parser_room(char *line, t_antler *antler, t_bool is_start, t_bool is_end)
{
	int		i;
	char	*str;
	t_room	*room;

	if (!(room = malloc(sizeof(t_room))))
		return ;
	if (is_start)
		antler->start = room;
	if (is_end)
		antler->end = room;
	room->have_way = FALSE;
	room->ant_no = 0;
	i = 0;
	if(!(str = ft_strchr(line, ' ')))
		error();
	*str = '\0';
	room->name = ft_strdup(line);
	i = (str - line) + 1;
	room->x = ft_atoi(line + i);
	str = ft_strchr(line + i, ' ');
	i = (str - line) + 1;
	if (!line[i])
		error();
	room->y = ft_atoi(line + i);
	str = ft_room2str(room);
	if (ft_strcmp(str, line) == 0)
	{
		free(line);
		error();
	}
	free(str);
	if (ft_findroom(room->name, antler)) // TODO X Y
		error();
	room->next = antler->rooms;
	antler->rooms = room;
}

void	lemin_parser_pipe(char *line, t_antler *antler)
{
	int i;
	t_pipe	*pipe;
	char	*str;

	if (!(pipe = malloc(sizeof(t_pipe))))
		return ;
	i = 0;
	if (!(str = ft_strchr(line, '-')))
		error();
	*str = '\0';
	pipe->a = ft_findroom(line, antler);
	i = (str - line) + 1;
	pipe->b = ft_findroom(line + i, antler);
	if (!pipe->a || !pipe->b)
		error();
	str = ft_pipe2str(pipe);
	if (ft_strcmp(str, line) == 0)
	{
		free(str);
		error();
	}
	free(str);
	pipe->next = antler->pipes;
	antler->pipes = pipe;
}

t_antler	*lemin_parser(void)
{
	char	*line;
	t_antler	*antler;
	t_bool	room_ended;
	t_bool	next_first;
	t_bool	next_end;
	int 	nbr_first;
	int 	nbr_end;


	if (!(antler = malloc(sizeof(t_antler))))
		return (NULL);
	antler->rooms = NULL;
	antler->pipes = NULL;
	lemin_parser_antnbr(antler);
	
	room_ended = FALSE;
	next_first = FALSE;
	next_end = FALSE;
	nbr_first = 0;
	nbr_end = 0;
	while (ft_gnl(STDIN_FILENO, &line))
	{
		if (*line != '#' && ft_strchr(line, ' '))
		{
			lemin_parser_room(line, antler, next_first, next_end);
		}
		else if (*line != '#')
		{
			room_ended = TRUE;
			lemin_parser_pipe(line, antler);
		}
		next_first = FALSE;
		next_end = FALSE;
		if (ft_strcmp(line, "##start") == 0)
		{
			if (nbr_first == 1)
				error();
			next_first++;
			next_first = TRUE;
		}
		else if (ft_strcmp(line, "##end") == 0)
		{
			if (nbr_end == 1)
				error();
			next_end++;
			next_end = TRUE;
		}
		if ((next_first || next_end) && room_ended)
		{
			ft_printf("??\n");
			error();
		}

		free(line);
		line = NULL;
	}
	return (antler);
}
