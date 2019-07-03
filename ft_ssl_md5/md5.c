#include <fcntl.h>
#include <sys/types.h>
#include <sys/uio.h>
#include <unistd.h>
#include <string.h>
#include <stdint.h>
#include <stdio.h>
#include <inttypes.h>

#include "ft_ssl.h"
#define LEFTROTATE(x, c) (((x) << (c)) | ((x) >> (32 - (c))))


uint32_t F(uint32_t X, uint32_t Y, uint32_t Z)
{
	return (X & Y) | ((~ X) & Z);
}

uint32_t G(uint32_t X, uint32_t Y, uint32_t Z)
{
	return (X & Z) | (Y & (~ Z));
}

uint32_t H(uint32_t X, uint32_t Y, uint32_t Z)
{
	return X ^ Y ^ Z;
}

uint32_t I(uint32_t X, uint32_t Y, uint32_t Z)
{
	return Y ^ (X | (~ Z));
}

int encrypt_md5(char *data, uint64_t size, t_params *params)
{
	char			message_padded[64];
	uint32_t		*message_padded32;
	int				i;
	uint32_t		A, B, C, D;

	uint32_t k[] = {
		0xd76aa478, 0xe8c7b756, 0x242070db, 0xc1bdceee,
		0xf57c0faf, 0x4787c62a, 0xa8304613, 0xfd469501,
		0x698098d8, 0x8b44f7af, 0xffff5bb1, 0x895cd7be,
		0x6b901122, 0xfd987193, 0xa679438e, 0x49b40821,
		0xf61e2562, 0xc040b340, 0x265e5a51, 0xe9b6c7aa,
		0xd62f105d, 0x02441453, 0xd8a1e681, 0xe7d3fbc8,
		0x21e1cde6, 0xc33707d6, 0xf4d50d87, 0x455a14ed,
		0xa9e3e905, 0xfcefa3f8, 0x676f02d9, 0x8d2a4c8a,
		0xfffa3942, 0x8771f681, 0x6d9d6122, 0xfde5380c,
		0xa4beea44, 0x4bdecfa9, 0xf6bb4b60, 0xbebfbc70,
		0x289b7ec6, 0xeaa127fa, 0xd4ef3085, 0x04881d05,
		0xd9d4d039, 0xe6db99e5, 0x1fa27cf8, 0xc4ac5665,
		0xf4292244, 0x432aff97, 0xab9423a7, 0xfc93a039,
		0x655b59c3, 0x8f0ccc92, 0xffeff47d, 0x85845dd1,
		0x6fa87e4f, 0xfe2ce6e0, 0xa3014314, 0x4e0811a1,
		0xf7537e82, 0xbd3af235, 0x2ad7d2bb, 0xeb86d391};

	uint32_t r[] = {7, 12, 17, 22, 7, 12, 17, 22, 7, 12, 17, 22, 7, 12, 17, 22,
		5,  9, 14, 20, 5,  9, 14, 20, 5,  9, 14, 20, 5,  9, 14, 20,
		4, 11, 16, 23, 4, 11, 16, 23, 4, 11, 16, 23, 4, 11, 16, 23,
		6, 10, 15, 21, 6, 10, 15, 21, 6, 10, 15, 21, 6, 10, 15, 21};


	memset(message_padded, 0, 64);
	memmove(message_padded, data, size);
	message_padded32 = (uint32_t*)message_padded;
	params->ds += size;


	if (size < 64 && FALSE == params->is_last) // end
	{
		params->is_last = TRUE;
		ft_printf("End1 : %lld\n", size);
		message_padded[size] = 0b10000000;
	}
	if (size < 56) // end
	{
		//size--;
		ft_printf("End2 : %lld\n", size);
		*((uint64_t *)(((char *)message_padded) + 56)) = 8 * params->ds;
	}


	if (0 == params->AA)
	{
		params->AA = 0x67452301;
		params->BB = 0xefcdab89;
		params->CC = 0x98badcfe;
		params->DD = 0x10325476;
	}



	A = params->AA;
	B = params->BB;
	C = params->CC;
	D = params->DD;

	for(i = 0; i<64; i++) {
		uint32_t f, g;

		if (i < 16) {
			f = F(B, C, D);
			g = i;
		} else if (i < 32) {
			f = G(B, C, D);
			g = (5*i + 1) % 16;
		} else if (i < 48) {
			f = H(B, C, D);
			g = (3*i + 5) % 16;          
		} else {
			f = I(B, C, D);
			g = (7*i) % 16;
		}
		uint32_t temp = D;
		D = C;
		C = B;
		B = B + LEFTROTATE((A + f + k[i] + message_padded32[g]), r[i]);
		A = temp;
	}
	params->AA = params->AA + A;
	params->BB = params->BB + B;
	params->CC = params->CC + C;
	params->DD = params->DD + D;

	printf("%08x%08x%08x%08x\n", swap_uint32(params->AA), swap_uint32(params->BB), swap_uint32(params->CC), swap_uint32(params->DD));
	return (0);
}
