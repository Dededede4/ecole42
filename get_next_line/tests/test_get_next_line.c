/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_get_next_line.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mprevot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/19 14:35:19 by mprevot           #+#    #+#             */
/*   Updated: 2016/12/19 15:29:44 by mprevot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include "../get_next_line.h"

int		main(void)
{
	char	*str;
	int		fd;
	char	rep[4][30] = {"bonjour,", "ci-join un join,", "", "Vive le love d'amour."};
	int		i = 0;

	fd = open("lvl0.txt", O_RDONLY);
	while (get_next_line(fd, &str))
	{
		ft_putendl(str);
		if (strcmp(rep[i], str) != 0)
			return (10 + i);
		i++;
	}
	return (0);
}
