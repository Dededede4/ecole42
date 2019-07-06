/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sha256.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mprevot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/05 16:24:29 by mprevot           #+#    #+#             */
/*   Updated: 2019/07/05 16:24:31 by mprevot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"
#include "sha256.h"

#define EP0(x) (RIGHTROTATE(x,2) ^ RIGHTROTATE(x,13) ^ RIGHTROTATE(x,22))
#define EP1(x) (RIGHTROTATE(x,6) ^ RIGHTROTATE(x,11) ^ RIGHTROTATE(x,25))
#define SIG0(x) (RIGHTROTATE(x,7) ^ RIGHTROTATE(x,18) ^ ((x) >> 3))
#define SIG1(x) (RIGHTROTATE(x,17) ^ RIGHTROTATE(x,19) ^ ((x) >> 10))

static void		init_params(t_params *p)
{
	if (0 == p->h0)
	{
		p->h0 = 0x6a09e667;
		p->h1 = 0xbb67ae85;
		p->h2 = 0x3c6ef372;
		p->h3 = 0xa54ff53a;
		p->h4 = 0x510e527f;
		p->h5 = 0x9b05688c;
		p->h6 = 0x1f83d9ab;
		p->h7 = 0x5be0cd19;
	}
}

#define ENCRYPT_INIT uint32_t A=p->h0,B=p->h1,C=p->h2,D=p->h3,i=0,t1,t2;
#define ENCRYPT_INIT2 uint32_t E=p->h4,F=p->h5,G=p->h6,H=p->h7;
#define ENCRYPT_END p->h0=p->h0+A;p->h1=p->h1+B;p->h2=p->h2+C;p->h3=p->h3+D;
#define ENCRYPT_END2 p->h4=p->h4+E;p->h5=p->h5+F;p->h6=p->h6+G;p->h7=p->h7+H;

static void		moulinette(t_params *p, uint32_t *m)
{
	ENCRYPT_INIT;
	ENCRYPT_INIT2;
	while (i < 64)
	{
		t1 = H + EP1(E) + ch(E, F, G) + g_sha256_k[i] + m[i];
		t2 = EP0(A) + maj(A, B, C);
		H = G;
		G = F;
		F = E;
		E = D + t1;
		D = C;
		C = B;
		B = A;
		A = t1 + t2;
		i++;
	}
	ENCRYPT_END;
	ENCRYPT_END2;
}

static void		generate_m(unsigned char *message_padded, uint32_t *m)
{
	uint32_t	i;
	uint32_t	j;

	i = 0;
	j = 0;
	while (i < 16)
	{
		m[i] = (message_padded[j] << 24) | (message_padded[j + 1] << 16)
		| (message_padded[j + 2] << 8) | (message_padded[j + 3]);
		i++;
		j += 4;
	}
	while (i < 64)
	{
		m[i] = SIG1(m[i - 2]) + m[i - 7] + SIG0(m[i - 15]) + m[(i) - 16];
		i++;
	}
}

int				encrypt_sha256(char *data, uint64_t size, t_params *p)
{
	unsigned char			message_padded[64];
	uint32_t				*message_padded32;
	uint32_t				m[64];

	memset(message_padded, 0, 64);
	memmove(message_padded, data, size);
	message_padded32 = (uint32_t*)message_padded;
	p->ds += size;
	if (size < 64 && FALSE == p->is_last && (p->is_last = TRUE))
		message_padded[size] = 0b10000000;
	if (size < 56)
		*((uint64_t *)((message_padded) + 56)) = swap_uint64(8 * p->ds);
	init_params(p);
	generate_m(message_padded, m);
	moulinette(p, m);
	if (size < 56)
		ft_printf("%08x%08x%08x%08x%08x%08x%08x%08x",
			p->h0, p->h1, p->h2, p->h3, p->h4, p->h5, p->h6, p->h7);
	return (0);
}
