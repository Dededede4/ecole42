#include <fcntl.h>
#include <sys/types.h>
#include <sys/uio.h>
#include <unistd.h>
#include <string.h>
#include <stdint.h>
#include <stdio.h>
#include <inttypes.h>
#include <byteswap.h>


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
/*
uint32_t BSIG0(uint32_t x)
{
	return RIGHTROTATE(x, 28) ^ RIGHTROTATE(x, 34) ^ RIGHTROTATE(x, 39);
}

uint32_t BSIG1(uint32_t x)
{
	return RIGHTROTATE(x, 14) ^ RIGHTROTATE(x, 18) ^ RIGHTROTATE(x, 41);
}


uint32_t SSIG0(uint32_t x){
	return RIGHTROTATE(x, 1) ^ RIGHTROTATE(x, 8) ^ (x >> 7);
}

uint32_t SSIG1(uint32_t x)
{
	return RIGHTROTATE(x, 19) ^ RIGHTROTATE(x, 61) ^ (x >> 6);
}*/

uint32_t swap_uint32( uint32_t val )
{
    val = ((val << 8) & 0xFF00FF00 ) | ((val >> 8) & 0xFF00FF ); 
    return (val << 16) | (val >> 16);
}

#define EP0(x) (RIGHTROTATE(x,2) ^ RIGHTROTATE(x,13) ^ RIGHTROTATE(x,22))
#define EP1(x) (RIGHTROTATE(x,6) ^ RIGHTROTATE(x,11) ^ RIGHTROTATE(x,25))
#define SIG0(x) (RIGHTROTATE(x,7) ^ RIGHTROTATE(x,18) ^ ((x) >> 3))
#define SIG1(x) (RIGHTROTATE(x,17) ^ RIGHTROTATE(x,19) ^ ((x) >> 10))


/*
   Initialiser un tableau de 64 entiers sur 32 bits T[1..64] tel que :
   T[i] = Int(232 * abs(sin i)) avec i en radians
   */



int main()
{
	//unsigned char	block[512];
	//ssize_t 		len;

	unsigned char			message[12] = "Hello World!";
	unsigned char			message_padded[64]; // 512 bits
	uint32_t		*message_padded32;

	uint32_t k[] = {
		0x428a2f98, 0x71374491, 0xb5c0fbcf, 0xe9b5dba5, 0x3956c25b, 0x59f111f1, 0x923f82a4, 0xab1c5ed5,
		0xd807aa98, 0x12835b01, 0x243185be, 0x550c7dc3, 0x72be5d74, 0x80deb1fe, 0x9bdc06a7, 0xc19bf174,
		0xe49b69c1, 0xefbe4786, 0x0fc19dc6, 0x240ca1cc, 0x2de92c6f, 0x4a7484aa, 0x5cb0a9dc, 0x76f988da,
		0x983e5152, 0xa831c66d, 0xb00327c8, 0xbf597fc7, 0xc6e00bf3, 0xd5a79147, 0x06ca6351, 0x14292967,
		0x27b70a85, 0x2e1b2138, 0x4d2c6dfc, 0x53380d13, 0x650a7354, 0x766a0abb, 0x81c2c92e, 0x92722c85,
		0xa2bfe8a1, 0xa81a664b, 0xc24b8b70, 0xc76c51a3, 0xd192e819, 0xd6990624, 0xf40e3585, 0x106aa070,
		0x19a4c116, 0x1e376c08, 0x2748774c, 0x34b0bcb5, 0x391c0cb3, 0x4ed8aa4a, 0x5b9cca4f, 0x682e6ff3,
		0x748f82ee, 0x78a5636f, 0x84c87814, 0x8cc70208, 0x90befffa, 0xa4506ceb, 0xbef9a3f7, 0xc67178f2
	};
/*
	uint32_t r[] = {7, 12, 17, 22, 7, 12, 17, 22, 7, 12, 17, 22, 7, 12, 17, 22,
		5,  9, 14, 20, 5,  9, 14, 20, 5,  9, 14, 20, 5,  9, 14, 20,
		4, 11, 16, 23, 4, 11, 16, 23, 4, 11, 16, 23, 4, 11, 16, 23,
		6, 10, 15, 21, 6, 10, 15, 21, 6, 10, 15, 21, 6, 10, 15, 21};*/


	memset(message_padded, 0, 64);
	memmove(message_padded, message, 12);

	message_padded32 = (uint32_t*)message_padded;

	int i = 0;
/*	for (i = 0; i < 16; i++)
	{
		F
		printf("val = 0x%" PRIx64 "\n", message_padded32[i]);
	}
*/
	message_padded[12] = 0b10000000;

	*((uint64_t *)(((char *)message_padded) + 56)) = __bswap_64(8 * 12); // La taille du Hello World !
printf("----");
	for (i = 0; i < 16; i++)
	{
		printf("val = 0x%" PRIx64 "\n", message_padded32[i]);
	}


	uint32_t m[64];
	uint32_t j, t1, t2;

	for (i = 0, j = 0; i < 16; ++i, j += 4)
		m[i] = (message_padded[j] << 24) | (message_padded[j + 1] << 16) | (message_padded[j + 2] << 8) | (message_padded[j + 3]);
	for ( ; i < 64; ++i)
		m[i] = SIG1(m[i - 2]) + m[i - 7] + SIG0(m[i - 15]) + m[i - 16];

	uint32_t A = 0x6a09e667;
	uint32_t B = 0xbb67ae85;
	uint32_t C = 0x3c6ef372;
	uint32_t D = 0xa54ff53a;
	uint32_t E = 0x510e527f;
	uint32_t F = 0x9b05688c;
	uint32_t G = 0x1f83d9ab;
	uint32_t H = 0x5be0cd19;

	uint32_t AA = 0x6a09e667;
	uint32_t BB = 0xbb67ae85;
	uint32_t CC = 0x3c6ef372;
	uint32_t DD = 0xa54ff53a;
	uint32_t EE = 0x510e527f;
	uint32_t FF = 0x9b05688c;
	uint32_t GG = 0x1f83d9ab;
	uint32_t HH = 0x5be0cd19;


	for (i = 0; i < 64; ++i) {
		t1 = H + EP1(E) + CH(E,F,G) + k[i] + m[i];
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

	A = AA + A;
	B = BB + B;
	C = CC + C;
	D = DD + D;
	E = EE + E;
	F = FF + F;
	G = GG + G;
	H = HH + H;


	printf("%08x%08x%08x%08x%08x%08x%08x%08x\n", (A), (B), (C), (D), (E), (F), (G), (H));
	printf("%08x%08x%08x%08x%08x%08x%08x%08x\n", swap_uint32(A), swap_uint32(B), swap_uint32(C), swap_uint32(D), swap_uint32(E), swap_uint32(F), swap_uint32(G), swap_uint32(H));
	return (0);
}




/*void sha256_final(SHA256_CTX *ctx, BYTE hash[])
{
	WORD i;

	i = ctx->datalen;

	// Pad whatever data is left in the buffer.
	if (ctx->datalen < 56) {
		ctx->data[i++] = 0x80;
		while (i < 56)
			ctx->data[i++] = 0x00;
	}
	else {
		ctx->data[i++] = 0x80;
		while (i < 64)
			ctx->data[i++] = 0x00;
		sha256_transform(ctx, ctx->data);
		memset(ctx->data, 0, 56);
	}

	// Append to the padding the total message's length in bits and transform.
	ctx->bitlen += ctx->datalen * 8;
	ctx->data[63] = ctx->bitlen;
	ctx->data[62] = ctx->bitlen >> 8;
	ctx->data[61] = ctx->bitlen >> 16;
	ctx->data[60] = ctx->bitlen >> 24;
	ctx->data[59] = ctx->bitlen >> 32;
	ctx->data[58] = ctx->bitlen >> 40;
	ctx->data[57] = ctx->bitlen >> 48;
	ctx->data[56] = ctx->bitlen >> 56;
	sha256_transform(ctx, ctx->data);

	// Since this implementation uses little endian byte ordering and SHA uses big endian,
	// reverse all the bytes when copying the final state to the output hash.
	for (i = 0; i < 4; ++i) {
		hash[i]      = (A >> (24 - i * 8)) & 0x000000ff;
		hash[i + 4]  = (B >> (24 - i * 8)) & 0x000000ff;
		hash[i + 8]  = (C >> (24 - i * 8)) & 0x000000ff;
		hash[i + 12] = (D >> (24 - i * 8)) & 0x000000ff;
		hash[i + 16] = (E >> (24 - i * 8)) & 0x000000ff;
		hash[i + 20] = (F >> (24 - i * 8)) & 0x000000ff;
		hash[i + 24] = (G >> (24 - i * 8)) & 0x000000ff;
		hash[i + 28] = (H >> (24 - i * 8)) & 0x000000ff;
	}
}*/
