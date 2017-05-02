/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_parsing.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mprevot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/26 16:37:33 by mprevot           #+#    #+#             */
/*   Updated: 2017/04/26 16:37:35 by mprevot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void			check_validity_gnl(int fd, int *nbr, int *total)
{
	char		*line;
	char		**splited;
	int			i;

	line = NULL;
	while (ft_gnl(fd, &line))
	{
		i = 0;
		splited = ft_strsplit(line, ' ');
		while (splited[i])
		{
			if (!ft_isdigit_str(splited[i]))
				ft_error("Error (no an digit)\n");
			i++;
		}
		if (*nbr == -1)
			*nbr = i;
		else if (*nbr != i)
			ft_error("Error (no an rectangle)\n");
		i++;
		*total += *nbr;
		ft_memdel((void**)&line);
		ft_strsplit_del(&splited);
	}
}

int				check_validity(char *path, int *width)
{
	int			fd;
	int			nbr;
	int			total;

	*width = -1;
	nbr = -1;
	fd = open(path, O_RDONLY);
	total = 0;
	if (fd > -1)
		check_validity_gnl(fd, &nbr, &total);
	else
		ft_error("Error (bad file)\n");
	close(fd);
	*width = nbr;
	return (total);
}

void			parsing_gnl(
	int fd, t_position **positions, int size, int x_vals)
{
	char		*line;
	char		**splited;
	size_t		x;
	size_t		y;
	int			i;

	line = NULL;
	y = 0;
	i = 0;
	while (ft_gnl(fd, &line))
	{
		x = 0;
		splited = ft_strsplit(line, ' ');
		while (splited[x])
		{
			positions[i] = ft_mlx_mallocposition(x * ((600 / x_vals * 10) / 16),
				y * ((600 / (size / x_vals)) * 10 / 16) + 200,
				200 - (ft_atoi(splited[x]) * 5));
			x++;
			i++;
		}
		ft_memdel((void**)&line);
		ft_strsplit_del(&splited);
		y++;
	}
}

t_position		**parsing(char *path, int width, int x_vals)
{
	t_position	**positions;
	int			fd;

	positions = ft_memalloc((width + 1) * sizeof(NULL));
	fd = open(path, O_RDONLY);
	if (fd > -1)
	{
		parsing_gnl(fd, positions, width, x_vals);
		close(fd);
		return (positions);
	}
	close(fd);
	ft_error("Error (bad file)\n");
	return (NULL);
}
