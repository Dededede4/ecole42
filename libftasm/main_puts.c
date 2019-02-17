#include <string.h>
int
     ft_puts(const char *s);
char *
     strdup(const char *s1);

int main_puts()
{
	char *str = strdup("Coucou mon coco");
	ft_puts(str);
	return 0;
}