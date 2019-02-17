#include <stdio.h>
#include <strings.h>
#include <stdlib.h>
#include <string.h>

char *
     ft_strcat(char *restrict s1, const char *restrict s2);
int main_strcat()
{
	char *a;
	char *b;
	char str[] = "Coucou mon coco";

	a = malloc(1000);
	b = malloc(1000);

	memcpy(a, str, strlen(str));
	memcpy(b, str, strlen(str));


	char *ta;
	char *tb;

	ta = ft_strcat(a, b);
	tb = strcat(a, b);

	if (0 == strcmp(ta, tb))
		printf("Bien : %s", a);
	else
		printf("Pas bien : %s alors que ça devrait être %s", ta, tb);
	return 0;
}
