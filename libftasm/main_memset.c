#include <stdio.h>
#include <strings.h>

void ft_memset(void *b, int c, size_t len);

int main()
{
	unsigned int a = -1;
	unsigned int b = -1;


	ft_memset(&a, 0, 3);
	memset(&b, 0, 3);
	if (a == b)
		printf("Bien");
	else
		printf("Pas bien : %x alors que ça devrait être %x", a, b);
	return 0;
}
