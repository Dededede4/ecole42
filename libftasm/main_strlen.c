#include <stdio.h>

size_t ft_strlen(char *str);

int main()
{
	if (6 == ft_strlen("abcdef"))
		printf("Youpi\n");
	else
		printf("Au lieu de 6 ça retourne : %zu \n", ft_strlen("abcde"));

	if (3 == ft_strlen("abc"))
		printf("Youpi\n");
	else
		printf("Au lieu de 3 ça retourne : %zu \n", ft_strlen("abc"));

}
