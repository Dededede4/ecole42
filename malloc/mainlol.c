#include <sys/mman.h>

int main()
{
	mmap(0, 4096 * 2, PROT_READ | PROT_WRITE, MAP_ANON|MAP_PRIVATE, -1, 0);
	return 0;
}
