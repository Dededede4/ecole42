#include <stdio.h>
#include <strings.h>

void * ft_memcpy(void *restrict dst, const void *restrict src, size_t n);

int main_memcpy()
{
	char str[] = "Coucou mon coco";
	int size = strlen(str);
	char destA[40];
	char destB[40];

	memcpy(destA, str, size);
	ft_memcpy(destB, str, size);

	if (0 == strcmp(destA, destB))
		printf("Bien : %s", destB);
	else
		printf("Pas bien : %s alors que ça devrait être %s", destA, destB);
	return 0;
}
