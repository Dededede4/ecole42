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

void	error(void)
{
	ft_putstr_fd("ERROR\n", STDERR_FILENO);
	exit(0);
}

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

void	lemin_parser_room(char *line, t_antler *antler)
{
	int		i;
	char	*str;
	t_room	*room;

	if (!(room = malloc(sizeof(t_room))))
		return ;
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

	if (!(antler = malloc(sizeof(t_antler))))
		return (NULL);
	antler->rooms = NULL;
	antler->pipes = NULL;
	lemin_parser_antnbr(antler);
	
	room_ended = FALSE;
	while (ft_gnl(STDIN_FILENO, &line))
	{
		if (ft_strchr(line, ' '))
		{
			if (room_ended)
				error();
			lemin_parser_room(line, antler);
		}
		else
		{
			room_ended = TRUE;
			lemin_parser_pipe(line, antler);
		}
		free(line);
	}
	return (antler);
}
