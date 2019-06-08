#include <fcntl.h>
#include <sys/types.h>
#include <sys/uio.h>
#include <unistd.h>

typedef struct {
  UINT4 state[4];                                   /* state (ABCD) */
  UINT4 count[2];        /* number of bits, modulo 2^64 (lsb first) */
  unsigned char buffer[64];                         /* input buffer */
} MD5_CTX;

void main()
{
	unsigned char	block[512];
	ssize_t 		len;

  context->state[0] = 0x67452301;
  context->state[1] = 0xefcdab89;
  context->state[2] = 0x98badcfe;
  context->state[3] = 0x10325476;
	while ((len = read(0, block, 512)) > 0)
	{
		printf("Pouet pd\n");
	}
}