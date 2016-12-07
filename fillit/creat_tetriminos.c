/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   creat_tetriminos.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmasiala <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/07 13:14:30 by fmasiala          #+#    #+#             */
/*   Updated: 2016/12/07 13:14:48 by fmasiala         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


t_tetri		*ft_tetrinew(char *tetri, size_t pos, char c)
{
	t_list	*new;

	new = (t_list *)malloc(sizeof(t_list));
	if (new == NULL)
		return (NULL);
	new->c = c;
	if (tetri[pos + 5] == '#')
		new->d = ft_tetrinew(tetri, pos + 5, c)
	if (tetri[pos + 4] == '#')
		new->l = ft_tetrinew(tetri, pos + 4, c)
	if (tetri[pos + 6] == '#')
		new->r = ft_tetrinew(tetri, pos + 6, c)
	new->t = NULL;
	return (new);
}

t_tetri		creat_tetriminos(char *argv[])
{
	t_tetri	**tetris;
	int		i;
	char	c = 'A';

	fd = ft_open(*argv[]);
	tetris = malloc(nbr * sizeof(t_tetri));
	i = 0;

	while((check = read(fd, str, 21)) >= 20)
	{

		tetris[i] = ft_tetrinew(ft_strchr(str, '#'), 0, c + i);
		i++;
	}
	close(fd);
	return (tetris);
}