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

int		check_end_file(int check, int last)
{
	if (check == 0 && last == 21)
	{
		ft_putstr("error\n");
		return (1);
	}
	return (0);
}

int		ft_error(int argc)
{
	if (argc != 2)
	{
		ft_putstr("usage: fillit input_file\n");
		return (1);
	}
	return (0);
}

int		tetri_checker(int check, char *str)
{
	if (check != 21 && check != 20)
	{
		ft_putstr("error\n");
		return (1);
	}
	if ((count_cara(str)) != 0)
	{
		ft_putstr("error\n");
		return (1);
	}
	return (0);
}
