/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reader.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmasiala <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/07 12:05:40 by fmasiala          #+#    #+#             */
/*   Updated: 2016/12/13 11:57:20 by fmasiala         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fillit.h"

int		ft_check_read(int *nbr, int *check,int fd)
{
	char	*str;
	int		last;

	str = ft_strnew(21);
	while ((*check = read(fd, str, 21)))
	{
		if (tetri_checker(*check, str) != 0)
			return (-1);
		(*nbr)++;
		last = *check;
	}
	return (last);
}

int		ft_istetriminos(char *str)
{
	int		i;
	int		count;

	i = 0;
	count = 0;
	while (i < 20)
	{
		if (str[i] == '#')
		{
			if ((i + 1) < 20 && str[i + 1] == '#')
				count++;
			if ((i - 1) >= 0 && str[i - 1] == '#')
				count++;
			if ((i + 5) < 20 && str[i + 5] == '#')
				count++;
			if ((i - 5) >= 0 && str[i - 5] == '#')
				count++;
		}
		i++;
	}
	if (count == 6 || count == 8)
		return (0);
	else
		return (-1);
}

int		count_cara(char *str)
{
	int		i;
	int		dot;
	int		diese;

	i = 0;
	dot = 0;
	diese = 0;
	if (str[i] == '\0')
		return (1);
	while (i < 21)
	{
		if (str[i] == '.')
			dot++;
		if (str[i] == '#')
			diese++;
		if (str[i] != '#' && str[i] != '.' && str[i] != '\n' && str[i] != '\0')
			return (-1);
		i++;
	}
	if (dot == 12 && diese == 4 && (ft_istetriminos(str) == 0))
		return (0);
	else
		return (-1);
}

int		ft_open(char *path)
{
	int		fd;

	if ((fd = open(path, O_RDONLY)) == -1)
	{
		ft_putstr("error\n");
		exit(2);
	}
	return (fd);
}

t_tetri	**reader(int argc, char *path, int *len)
{
	int		fd;
	int		check;
	int		last;
	t_tetri **tetris;

	if (ft_error(argc) == -1)
		exit(0);
	check = 0;
	last = 0;
	fd = ft_open(path);
	if ((last = ft_check_read(len, &check, fd)) == -1)
		exit(0);
	if (check_end_file(check, last) != 0)
			exit (0);
	tetris = creat_tetriminos(path, *len);
	close(fd);
	return (tetris);
}
