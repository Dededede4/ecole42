/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmasiala <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/22 09:04:34 by fmasiala          #+#    #+#             */
/*   Updated: 2016/11/22 09:05:08 by fmasiala         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include "libft.h"

int		error(int argc);
int		ft_check(char *str);
int		count_cara(char *str);
void	free_list(List *list);

int		main(int argc, char const *argv[])
{
	int		fd;
	int		i;
	int		check;
	char	*str;
	if (error(argc) == -1)
	{
		exit(0);
	}
	if ((fd = open(argv[1], O_RDONLY)) == -1)
	{
		ft_putstr("Error\n");
		exit(0);
	}
	i = 0;
	check = 0;
	str[i] = ft_strnew(21);
	while((check = read(fd, str[i], 21)) >= 20)
	{
		if ((count_cara(str[i])) != 0)
		{
			ft_putstr("Piece invalide\n");
			ft_putstr(str[i]);
			return (1);
		}
	}
	close(fd);
	//free(str);
}

/******************************************************/

int		error(int argc)
{
	if (argc != 2)
	{
		ft_putstr("usage: fillit valid_sample.txt\n");
		return (-1);
	}
	return (0);
}

/*****************************************************/

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

/*int		ft_check(char *str)
{
	int ret;

	ret = ft_count_cara(str);
	return (ret);
}*/

/*****************************************************/




