#include <stdio.h>

size_t ft_strlenMAFONCTIONAMOI(char *str);

int main()
{
	if (6 == ft_strlenMAFONCTIONAMOI("abcdef"))
		printf("Youpi\n");
	else
		printf("Au lieu de 6 ça retourne : %zu \n", ft_strlenMAFONCTIONAMOI("abcde"));

	if (3 == ft_strlenMAFONCTIONAMOI("abc"))
		printf("Youpi\n");
	else
		printf("Au lieu de 3 ça retourne : %zu \n", ft_strlenMAFONCTIONAMOI("abc"));

}
