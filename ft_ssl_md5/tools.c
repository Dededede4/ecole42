/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mprevot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/02 20:18:19 by mprevot           #+#    #+#             */
/*   Updated: 2019/07/02 20:18:24 by mprevot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

uint32_t swap_uint32( uint32_t val )
{
	val = ((val << 8) & 0xFF00FF00 ) | ((val >> 8) & 0xFF00FF ); 
	return (val << 16) | (val >> 16);
}

void	get_file(t_params *params)
{
	int		size;
	char	buf[1024];
	char	*save;

	while ((size = read(params->fd, buf, 1024)) > 0)
	{
		//size--;
		
		if(NULL == params->d)
			params->d = ft_memdup(buf, params->ds + size);
		else
		{
			save = params->d;
			params->d = ft_memalloc(params->ds + size);
			ft_memcpy(params->d, save, params->ds);
			ft_memcpy(params->d + params->ds, buf, size);
			free(save);
		}
		params->ds += size;
	}
}
	