/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   antitroll.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mprevot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/15 04:33:42 by mprevot           #+#    #+#             */
/*   Updated: 2018/12/15 04:33:46 by mprevot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "antitroll.h"

void			ifexit(t_bool cond, int nbr)
{
	if (cond)
		exit(nbr);
}

void			antitroll(char *ptr, off_t size)
{
	unsigned int	magic_number;

	ifexit((size < (off_t)sizeof(struct fat_header)), 42);
	magic_number = *(int*)ptr;
	if (magic_number == MH_MAGIC_64)
		handle_64_trololo(ptr, size);
	else if (magic_number == MH_MAGIC)
		handle_32_trololo(ptr, size);
	else if (magic_number == FAT_CIGAM)
		handle_fat_trololo(ptr, size);
}

unsigned int	ft_nxswaplong(unsigned int nbr)
{
	unsigned int	result;
	char			*sub_result;
	char			*sub_nbr;

	sub_nbr = (char *)&nbr;
	sub_result = (char *)&result;
	sub_result[0] = sub_nbr[3];
	sub_result[1] = sub_nbr[2];
	sub_result[2] = sub_nbr[1];
	sub_result[3] = sub_nbr[0];
	return (result);
}

unsigned int	nsl(unsigned int nbr)
{
	return (ft_nxswaplong(nbr));
}
