#include <stdio.h>
#include <strings.h>

void ft_bzero(void *s, size_t n);

int main()
{
	unsigned int a = -1;
	unsigned int b = -1;


	ft_bzero(&a, 3);
	bzero(&b, 3);
	if (a == b)
		printf("Bien");
	else
		printf("Pas bien : %x alors que ça devrait être %x", a, b);
	return 0;
}
