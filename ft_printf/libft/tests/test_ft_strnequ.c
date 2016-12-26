/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_ft_strequ.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mprevot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/28 14:33:26 by mprevot           #+#    #+#             */
/*   Updated: 2016/11/28 14:55:04 by mprevot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

int		main(void)
{
	if (ft_strnequ("coucoubg", "coucoubg", 10) != 1)
		return (10);
	if (ft_strnequ("couco", "coucou", 10) != 0)
		return (20);
	if (ft_strnequ("", "", 10) != 1)
		return (30);
	if (ft_strnequ("coucoubg", "coucoull", 6) != 1)
		return (40);
	if (ft_strnequ("coucoubg", "coucokll", 6) != 0)
		return (40);

}
