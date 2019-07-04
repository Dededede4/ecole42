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

int encrypt_sha256(char *data, uint64_t size, t_params *params)
{

	unsigned char			message_padded[64]; // 512 bits
	uint32_t		*message_padded32, i;
	uint32_t m[64];
	uint32_t j, t1, t2;

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
	{
		*((uint64_t *)(((char *)message_padded) + 56)) = ENDIAN_SWAP_U64(8 * params->ds);
	}
	if (0 == params->AA)
	{
		params->AA = 0x6a09e667;
		params->BB = 0xbb67ae85;
		params->CC = 0x3c6ef372;
		params->DD = 0xa54ff53a;
		params->EE = 0x510e527f;
		params->FF = 0x9b05688c;
		params->GG = 0x1f83d9ab;
		params->HH = 0x5be0cd19;
	}

	

	for (i = 0, j = 0; i < 16; ++i, j += 4)
		m[i] = (message_padded[j] << 24) | (message_padded[j + 1] << 16) | (message_padded[j + 2] << 8) | (message_padded[j + 3]);
	for ( ; i < 64; ++i)
		m[i] = SIG1(m[i - 2]) + m[i - 7] + SIG0(m[i - 15]) + m[i - 16];

	uint32_t A = params->AA;
	uint32_t B = params->BB;
	uint32_t C = params->CC;
	uint32_t D = params->DD;
	uint32_t E = params->EE;
	uint32_t F = params->FF;
	uint32_t G = params->GG;
	uint32_t H = params->HH;


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

	params->AA = params->AA + A;
	params->BB = params->BB + B;
	params->CC = params->CC + C;
	params->DD = params->DD + D;
	params->EE = params->EE + E;
	params->FF = params->FF + F;
	params->GG = params->GG + G;
	params->HH = params->HH + H;

	if (size < 56)
		ft_printf("%08x%08x%08x%08x%08x%08x%08x%08x", (params->AA), (params->BB), (params->CC), (params->DD), (params->EE), (params->FF), (params->GG), (params->HH));
	return (0);
}