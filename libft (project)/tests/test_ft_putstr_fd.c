/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_ft_putstr_fd.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mprevot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/29 14:02:15 by mprevot           #+#    #+#             */
/*   Updated: 2016/11/29 14:03:12 by mprevot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

int		main(void)
{
	int     p[2];
	char    sortie[100];

	pipe(p);

	ft_putstr_fd("coucoupouet", p[1]);
	sortie[read(p[0], sortie, 100)] = '\0';
	if (0 != strcmp(sortie, "coucoupouet"))
		return (10);

	return (0);
}
