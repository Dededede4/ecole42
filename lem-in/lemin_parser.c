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

void			lemin_parser_antnbr(t_antler *antler)
{
	char	*ant_nbr;

	ft_gnl(STDIN_FILENO, &ant_nbr);
	if (!(ft_isdigit_str(ant_nbr)))
		error();
	antler->ant_nbr_global = ft_atoi(ant_nbr);
	if (antler->ant_nbr_global == 0)
		error();
	antler->ant_nbr_start = antler->ant_nbr_global;
	free(ant_nbr);
}

void			lemin_parser_room(char *line, t_antler *antler,
	t_bool is_start, t_bool is_end)
{
	int		i;
	char	*str;
	t_room	*room;

	if (!(room = newroom(antler, is_start, is_end)))
		error();
	i = 0;
	if (!(str = ft_strchr(line, ' ')))
		error();
	*str = '\0';
	if (ft_findroom(line, antler))
		error();
	room->name = ft_strdup(line);
	*str = ' ';
	i = (str - line) + 1;
	room->x = ft_atoi(line + i);
	str = ft_strchr(line + i, ' ');
	i = (str - line) + 1;
	if (!line[i])
		error();
	room->y = ft_atoi(line + i);
	str = ft_room2str(room);
	if (ft_strcmp(str, line) != 0)
		error();
	free(str);
}

t_bool			lemin_parser_pipe(char *line, t_antler *antler)
{
	int			i;
	t_pipe		*pipe;
	char		*str;

	if (!(pipe = malloc(sizeof(t_pipe))))
		error();
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
	return (TRUE);
}

/*
** 	b[0] room_ended = FALSE;
**	b[1] next_first = FALSE;
**	b[2] next_end = FALSE;
*/

t_antler		*lemin_parser(void)
{
	char		*line;
	t_antler	*antler;
	t_bool		b[3];

	antler = newantler();
	lemin_parser_antnbr(antler);
	ft_bzero(&b, 3);
	while (ft_gnl(STDIN_FILENO, &line))
	{
		antler->input = ft_strjoin_multi(TRUE, antler->input,
			ft_strdup(line), ft_strdup("\n"), NULL);
		if (*line != '#' && ft_strchr(line, ' '))
			lemin_parser_room(line, antler, b[1], b[2]);
		else if (*line != '#')
			b[0] = lemin_parser_pipe(line, antler);
		b[1] = (ft_strcmp(line, "##start") == 0);
		b[2] = (ft_strcmp(line, "##end") == 0);
		if ((b[1] || b[2]) && b[0])
			error();
		free(line);
	}
	if (!antler->start || !antler->end)
		error();
	return (antler);
}
