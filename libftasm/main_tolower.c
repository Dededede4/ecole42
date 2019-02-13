#include <ctype.h>

int	tolower(int c);
int	ft_tolower(int c);
int main()
{
	for (int i = 0; i < 2555; ++i)
	{
		if(tolower(i) != ft_tolower(i))
		{
			printf("Error for %i.\n", i);
		}
	}
	printf("No error ? So it's OK.\n");
	return 0;
}