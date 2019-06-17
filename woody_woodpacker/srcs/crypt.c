# include "woody.h"

int 		gen_secret(unsigned char *secret)
{
	int	fd;


	if ((fd = open("/dev/random", O_RDONLY)) < 0) {
		perror("open");
		return -1;
	}
	if (read(fd, secret, 8) < 0) {
		perror("read");
		return -1;
	}
	return 0;
}

void		encrypt_main(void *bin, size_t len, unsigned char *secret)
{
	size_t	rot = 0;
	size_t i = 0;

	(void)bin;
	(void)secret;
	while (i < len) {
		((unsigned char*)bin)[i] = ((unsigned char*)bin)[i] ^ secret[rot];
		i++;
		rot = rot == 7 ? 0 : rot + 1;
	}
}
