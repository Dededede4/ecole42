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


#define LEFTROTATE(x, c) (((x) << (c)) | ((x) >> (32 - (c))))
#define RIGHTROTATE(x, c) (((x) >> (c)) | ((x) << (32 - (c))))


uint32_t CH(uint32_t x, uint32_t y, uint32_t z)
{
	return (x & y) ^ ( (~ x) & z);
}

uint32_t MAJ(uint32_t x, uint32_t y, uint32_t z)
{
	return (x & y) ^ (x & z) ^ (y & z);
}

#define EP0(x) (RIGHTROTATE(x,2) ^ RIGHTROTATE(x,13) ^ RIGHTROTATE(x,22))
#define EP1(x) (RIGHTROTATE(x,6) ^ RIGHTROTATE(x,11) ^ RIGHTROTATE(x,25))
#define SIG0(x) (RIGHTROTATE(x,7) ^ RIGHTROTATE(x,18) ^ ((x) >> 3))
#define SIG1(x) (RIGHTROTATE(x,17) ^ RIGHTROTATE(x,19) ^ ((x) >> 10))

static void		init_params(t_params *p)
{
	if (0 == p->AA)
	{
		p->AA = 0x6a09e667;
		p->BB = 0xbb67ae85;
		p->CC = 0x3c6ef372;
		p->DD = 0xa54ff53a;
		p->EE = 0x510e527f;
		p->FF = 0x9b05688c;
		p->GG = 0x1f83d9ab;
		p->HH = 0x5be0cd19;
	}
}

#define ENCRYPT_INIT uint32_t A=p->AA,B=p->BB,C=p->CC,D=p->DD,i=0,t1,t2;
#define ENCRYPT_INIT2 uint32_t E=p->EE,F=p->FF,G=p->GG,H=p->HH;
#define ENCRYPT_END p->AA=p->AA+A;p->BB=p->BB+B;p->CC=p->CC+C;p->DD=p->DD+D;
#define ENCRYPT_END2 p->EE=p->EE+E;p->FF=p->FF+F;p->GG=p->GG+G;p->HH=p->HH+H;

static void moulinette(t_params *p, uint32_t *m)
{
	ENCRYPT_INIT;
	ENCRYPT_INIT2;
	for (i = 0; i < 64; ++i) {
		t1 = H + EP1(E) + CH(E,F,G) + sha256_k[i] + m[i];
		t2 = EP0(A) + MAJ(A,B,C);
		H = G;
		G = F;
		F = E;
		E = D + t1;
		D = C;
		C = B;
		B = A;
		A = t1 + t2;
	}
	ENCRYPT_END;
	ENCRYPT_END2;
}

static void generate_m(unsigned char *message_padded, uint32_t *m)
{
	uint32_t	i = 0, j = 0;
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

int encrypt_sha256(char *data, uint64_t size, t_params *p)
{
	unsigned char			message_padded[64]; // 512 bits
	uint32_t		*message_padded32;
	uint32_t m[64];

	memset(message_padded, 0, 64);
	memmove(message_padded, data, size);
	message_padded32 = (uint32_t*)message_padded;
	p->ds += size;
	if (size < 64 && FALSE == p->is_last && (p->is_last = TRUE))
		message_padded[size] = 0b10000000;
	if (size < 56)
		*((uint64_t *)(((char *)message_padded) + 56)) = ENDIAN_SWAP_U64(8 * p->ds);
	init_params(p);
	generate_m(message_padded, m);
	moulinette(p, m);
	if (size < 56)
		ft_printf("%08x%08x%08x%08x%08x%08x%08x%08x",
			p->AA, p->BB, p->CC, p->DD, p->EE, p->FF, p->GG, p->HH);
	return (0);
}
