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

uint32_t	swap_uint32(uint32_t val)
{
	uint32_t		new;
	unsigned char	*n;
	unsigned char	*o;

	o = (unsigned char *)&val;
	n = (unsigned char *)&new;
	n[0] = o[3];
	n[1] = o[2];
	n[2] = o[1];
	n[3] = o[0];
	return (new);
}

uint64_t	swap_uint64(uint64_t val)
{
	uint64_t		new;
	unsigned char	*n;
	unsigned char	*o;

	o = (unsigned char *)&val;
	n = (unsigned char *)&new;
	n[0] = o[7];
	n[1] = o[6];
	n[2] = o[5];
	n[3] = o[4];
	n[4] = o[3];
	n[5] = o[2];
	n[6] = o[1];
	n[7] = o[0];
	return (new);
}
