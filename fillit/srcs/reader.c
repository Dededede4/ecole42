/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reader.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmasiala <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/07 12:05:40 by fmasiala          #+#    #+#             */
/*   Updated: 2016/12/07 12:05:49 by fmasiala         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int		ft_istetriminos(char *str)
{
	int		i;
	int		count;
	int		flag;

	i = 0;
	count = 0;
	flag = 0;
	while (i < 21)
	{
		if (str[i] == '#')
		{
			count++;
			if ((str[i + 1] == '#') || (str[i - 1] == '#') || (str[i + 5] == '#') || (str[i - 5] == '#'))
			{
				flag++;
			}
		}
		i++;
	}
	if (flag == count)
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
	if (dot == 12 && diese == 4 && (ft_istetriminos(str) == 0) )
		return (0);
	else
		return (-1);
}

int		error(int argc)
{
	if (argc != 2)
	{
		ft_putstr("usage: fillit valid_sample.txt\n");
		return (-1);
	}
	return (0);
}

int		ft_open(char *argc[])
{
	int		fd;

	if ((fd = open(argv[1], O_RDONLY)) == -1)
	{
		ft_putstr("Error\n");
		exit(0);
	}
	return (fd);
}

t_tetri		reader(int argc, char *argv[], int	*len)
{
	int		fd;
	int		i;
	int		check;
	int     nbr;
	char	*str;

	nbr = 0;
	*len = 0;
	if (error(argc) == -1)
	{
		exit(0);
	}
	i = 0;
	check = 0;
	str = ft_strnew(21);
	fd = ft_open(*argv[]);
	while((check = read(fd, str, 21)) >= 20)
	{
		if ((count_cara(str)) != 0)
		{
			ft_putstr("Piece invalide\n");
			ft_putstr(str);
			return (1);
		}
		str[20] = '\0';
		nbr++;
	}
	creat_tetriminos(*arg[]);
	*len = nbr;
	close(fd);
}
