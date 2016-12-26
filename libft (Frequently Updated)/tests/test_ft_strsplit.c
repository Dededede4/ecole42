/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_ft_strsplit.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mprevot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/28 17:43:30 by mprevot           #+#    #+#             */
/*   Updated: 2016/11/28 19:13:47 by mprevot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

int		main(void)
{
	char **str = ft_strsplit("salut*les***etudiants*", '*');

	if (strcmp(str[0], "salut") != 0)
		return (10);
	if (strcmp(str[1], "les") != 0)
		return (20);
	if (strcmp(str[2], "etudiants") != 0)
		return (30);
	if (str[3] != NULL)
		return (40);

	str = ft_strsplit("**salut*les***etudiants", '*');

	if (strcmp(str[0], "salut") != 0)
		return (50);
	if (strcmp(str[1], "les") != 0)
		return (60);
	if (strcmp(str[2], "etudiants") != 0)
		return (70);
	if (str[3] != NULL)
		return (80);

	return (0);
}
