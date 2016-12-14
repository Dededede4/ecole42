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

int		ft_check_file(int *nbr, int *check, int fd)
{
	char	*str;
	int		last;

	last = 0;
	str = ft_strnew(21);
	while ((*check = read(fd, str, 21)))
	{
		if ((*check != 21 && *check != 20) || (ft_check_syntax(str)) != 0)
		{
			ft_putstr("error\n");
			return (-1);
		}
		(*nbr)++;
		last = *check;
	}
	return (last);
}

int		ft_check_disposition(char *str)
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

int		ft_check_syntax(char *str)
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
	if (dot == 12 && diese == 4 && (ft_check_disposition(str) == 0))
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

t_tetri	**ft_reader(int argc, char *path, int *len)
{
	int		fd;
	int		check;
	int		last;
	t_tetri **tetris;

	if (argc != 2)
	{
		ft_putstr_fd("usage: fillit input_file\n", 0);
		exit(1);
	}
	check = 0;
	last = 0;
	fd = ft_open(path);
	if ((last = ft_check_file(len, &check, fd)) == -1)
		exit(0);
	if ((check == 0 && last == 21) || (check == 0 && last == 0))
	{
		ft_putstr("error\n");
		exit(0);
	}
	tetris = ft_creat_tetriminos(path, *len);
	close(fd);
	return (tetris);
}
