/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_rev_nbr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heynard <heynard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/29 15:37:56 by heynard           #+#    #+#             */
/*   Updated: 2017/05/11 22:47:43 by heynard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"

intmax_t			ft_rev_nbr(intmax_t nbr, int *nb_of_zero)
{
	intmax_t		ret;
	int				start;

	start = 1;
	ret = 0;
	while (nbr > 0)
	{
		ret *= 10;
		if (nbr % 10 == 0 && start)
			(*nb_of_zero)++;
		else
			start = 0;
		ret += nbr % 10;
		nbr /= 10;
	}
	return (ret);
}
