#include <stdio.h>
#include <strings.h>
#include <stdlib.h>
     #include <string.h>
char *ft_strdup(const char *s1);

int main_strdup()
{
	char str[] = "Coucou mon coco";
	char *destA;
	char *destB;

	destA = ft_strdup(str);
	destB = strdup(str);

	if (0 == strcmp(destA, destB))
		printf("Bien : %s", destB);
	else
		printf("Pas bien : %s alors que ça devrait être %s", destA, destB);
	return 0;
}
