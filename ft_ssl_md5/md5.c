/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   md5.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mprevot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/04 11:21:56 by mprevot           #+#    #+#             */
/*   Updated: 2019/07/04 11:21:58 by mprevot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"
#include "md5.h"

static void		init_params(t_params *params)
{
	if (0 == params->AA)
	{
		params->AA = 0x67452301;
		params->BB = 0xefcdab89;
		params->CC = 0x98badcfe;
		params->DD = 0x10325476;
	}
}

#define MOULINETTE_VARS uint32_t	i = 0, a, b, c, d, f, g, temp;
#define MOULINETTE_INITS a=p->AA;b=p->BB;c=p->CC;d=p->DD;
#define MOULINETTE_END p->AA=p->AA+a;p->BB=p->BB+b;p->CC=p->CC+c;p->DD=p->DD+d;

static void		moulinette(uint32_t *message_padded32, t_params *p)
{
	MOULINETTE_VARS;
	MOULINETTE_INITS;
	while (i < 64)
	{
		if (i < 16)
			g = i;
		else if (i < 32)
			g = (5 * i + 1) % 16;
		else
			g = (i < 48) ? (3 * i + 5) % 16 : (7 * i) % 16;
		if (i < 16)
			f = func_f(b, c, d);
		else if (i < 32)
			f = func_g(b, c, d);
		else
			f = (i < 48) ? func_h(b, c, d) : func_i(b, c, d);
		temp = d;
		d = c;
		c = b;
		b = b + LEFTROTATE((a + f + k[i] + message_padded32[g]), r[i]);
		a = temp;
		i++;
	}
	MOULINETTE_END;
}

int				encrypt_md5(char *data, uint64_t size, t_params *p)
{
	char			message_padded[64];
	uint32_t		*message_padded32;

	memset(message_padded, 0, 64);
	memmove(message_padded, data, size);
	message_padded32 = (uint32_t*)message_padded;
	p->ds += size;
	if (size < 64 && FALSE == p->is_last)
	{
		p->is_last = TRUE;
		message_padded[size] = 0b10000000;
	}
	if (size < 56)
		*((uint64_t *)(((char *)message_padded) + 56)) = 8 * p->ds;
	init_params(p);
	moulinette(message_padded32, p);
	if (size < 56)
		ft_printf("%08x%08x%08x%08x", swap_uint32(p->AA),
			swap_uint32(p->BB), swap_uint32(p->CC), swap_uint32(p->DD));
	return (0);
}
