/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_ft_strequ.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mprevot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/28 14:33:26 by mprevot           #+#    #+#             */
/*   Updated: 2016/11/28 14:35:45 by mprevot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

int		main(void)
{
	if (ft_strequ("coucoubg", "coucoubg") != 1)
		return (10);
	if (ft_strequ("couco", "coucou") != 0)
		return (20);
	if (ft_strequ("", "") != 1)
		return (30);
}
