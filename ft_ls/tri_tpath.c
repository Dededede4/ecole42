/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tri_tpath.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mprevot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/17 21:14:57 by mprevot           #+#    #+#             */
/*   Updated: 2017/07/17 21:14:59 by mprevot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int		tri_asc_size_path(void *f1, void *f2)
{
	return (get_bytes((((t_path *)f1)->path)) -
		get_bytes(((t_path *)f2)->path));
}

int		tri_asc_time_path(void *f1, void *f2)
{
	return ((get_time(((t_path *)f1)->path)) <
		get_time(((t_path *)f2)->path));
}

int		tri_asc_ascii_path(void *f1, void *f2)
{
	return (ft_strcmp(((t_path *)f1)->path, ((t_path *)f2)->path));
}
