#include <fcntl.h>
#include <sys/types.h>
#include <sys/uio.h>
#include <unistd.h>
#include <string.h>

typedef struct {
  UINT4 state[4];                                   /* state (ABCD) */
  UINT4 count[2];        /* number of bits, modulo 2^64 (lsb first) */
  unsigned char buffer[64];                         /* input buffer */
} MD5_CTX;

void main()
{
	unsigned char	block[512];
	ssize_t 		len;

	char			message[12] = "Hello World!";
	char			message_padded[64]; // 512 bits

	bzero(message_padded, 64);
	memmove(message_padded, src, 12);
	message_padded[13] = 0b10000000;

	*((t_uint64*)(message_padded + 56)) = 8 * 12; // La taille du Hello World !



	context->state[0] = 0x67452301;
	context->state[1] = 0xefcdab89;
	context->state[2] = 0x98badcfe;
	context->state[3] = 0x10325476;
	while ((len = read(0, block, 512)) > 0)
	{
		printf("Pouet pd\n");
	}
}
