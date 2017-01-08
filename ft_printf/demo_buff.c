#include <stdio.h>
#include <unistd.h>

int	main(void)
{
	printf("bon");
	fflush(stdout);
	write(1, "jour", 4);
}
