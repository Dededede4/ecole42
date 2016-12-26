/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_ft_putchar_fd.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mprevot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/29 13:58:19 by mprevot           #+#    #+#             */
/*   Updated: 2016/11/29 13:59:13 by mprevot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

int		main(void)
{
	int     p[2];
	char    sortie[100];

	pipe(p);

	ft_putchar_fd('Q', p[1]);
	sortie[read(p[0], sortie, 100)] = '\0';
	if (0 != strcmp(sortie, "Q"))
		return (10);

	return (0);
}
