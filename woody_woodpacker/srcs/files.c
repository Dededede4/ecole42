#include "woody.h"

int	write_file(char const *map, int64_t const size)
{
	int	fd;

	fd = open("woody", O_RDWR|O_CREAT|O_TRUNC, 0755);
	if (fd < 0) {
		perror("open");
		return -1;
	}
	write(fd, map, size);
	close(fd);
	return 0;
}

int	dump_woody(void *map, int const fd, int64_t const size)
{
	int	retval1;
	int	retval2;
	int	retval3;

	retval1 = write_file(map, size);
	retval2 = munmap(map, size);
	if (retval2 < 0)
		perror("munmap");
	retval3 = close(fd);
	if (retval3 < 0)
		perror("close");
	if (retval1 || retval2 || retval3)
		return 1;
	return 0;
}

int		open_file(char const *name, int64_t *size, int const mod)
{
	int	fd;

	fd = open(name, mod);
	if (fd < 0) {
		perror("open");
	} else {
		*size = lseek(fd, 0, SEEK_END);
		if (*size < 0) {
			perror("lseek");
			close(fd);
			fd = -1;
		}
	}
	return fd;
}


