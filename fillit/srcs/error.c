/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmasiala <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/09 08:59:34 by fmasiala          #+#    #+#             */
/*   Updated: 2016/12/13 11:56:01 by fmasiala         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fillit.h"

int		ft_check_end_file(int check, int last)
{
	if ((check == 0 && last == 21) || (check == 0 && last == 0))
	{
		ft_putstr("error\n");
		return (1);
	}
	return (0);
}
