/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmasiala <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/09 08:59:34 by fmasiala          #+#    #+#             */
/*   Updated: 2016/12/09 08:59:44 by fmasiala         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fillit.h"

int		error(int argc)
{
	if (argc != 2)
	{
		ft_putstr_fd("usage: fillit valid_sample.txt\n", 0);
		return (-1);
	}
	return (0);
}

int		tetri_checker(int check, char *str)
{
	if (check != 21 && check != 20)
	{
		ft_putstr_fd("Piece invalide\n", 0);
		return (1);
	}
	if ((count_cara(str)) != 0)
	{
		ft_putstr_fd("Piece invalide\n", 0);
		return (1);
	}
	return (0);
}
