/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tri_tfile.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mprevot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/17 21:15:16 by mprevot           #+#    #+#             */
/*   Updated: 2017/07/17 21:15:18 by mprevot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int		tri_asc_size(void *f1, void *f2)
{
	return (((t_file *)f1)->bytes - ((t_file *)f2)->bytes);
}

int		tri_asc_time(void *f1, void *f2)
{
	return (((t_file *)f1)->modified.tv_sec < ((t_file *)f2)->modified.tv_sec);
}

int		tri_asc_ascii(void *f1, void *f2)
{
	return (ft_strcmp(((t_file *)f1)->name, ((t_file *)f2)->name));
}
