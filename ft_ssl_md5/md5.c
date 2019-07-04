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

uint32_t	func_f(uint32_t x, uint32_t y, uint32_t z)
{
	return ((x & y) | ((~x) & z));
}

uint32_t	func_g(uint32_t x, uint32_t y, uint32_t z)
{
	return ((x & z) | (y & (~z)));
}

uint32_t	func_h(uint32_t x, uint32_t y, uint32_t z)
{
	return (x ^ y ^ z);
}

uint32_t	func_i(uint32_t x, uint32_t y, uint32_t z)
{
	return (y ^ (x | (~z)));
}

int			encrypt_md5(char *data, uint64_t size, t_params *params)
{
	char			message_padded[64];
	uint32_t		*message_padded32, a, b, c, d, g, i, f, temp;

	memset(message_padded, 0, 64);
	memmove(message_padded, data, size);
	message_padded32 = (uint32_t*)message_padded;
	params->ds += size;
	if (size < 64 && FALSE == params->is_last) // end
	{
		params->is_last = TRUE;
		message_padded[size] = 0b10000000;
	}
	if (size < 56) // end
		*((uint64_t *)(((char *)message_padded) + 56)) = 8 * params->ds;
	if (0 == params->AA)
	{
		params->AA = 0x67452301;
		params->BB = 0xefcdab89;
		params->CC = 0x98badcfe;
		params->DD = 0x10325476;
	}
	a = params->AA;
	b = params->BB;
	c = params->CC;
	d = params->DD;
	for(i = 0; i<64; i++) {
		if (i < 16) {
			f = func_f(b, c, d);
			g = i;
		} else if (i < 32) {
			f = func_g(b, c, d);
			g = (5*i + 1) % 16;
		} else if (i < 48) {
			f = func_h(b, c, d);
			g = (3*i + 5) % 16;          
		} else {
			f = func_i(b, c, d);
			g = (7*i) % 16;
		}
		temp = d;
		d = c;
		c = b;
		b = b + LEFTROTATE((a + f + k[i] + message_padded32[g]), r[i]);
		a = temp;
	}
	params->AA = params->AA + a;
	params->BB = params->BB + b;
	params->CC = params->CC + c;
	params->DD = params->DD + d;
	if (size < 56)
		ft_printf("%08x%08x%08x%08x", swap_uint32(params->AA), swap_uint32(params->BB), swap_uint32(params->CC), swap_uint32(params->DD));
	return (0);
}
