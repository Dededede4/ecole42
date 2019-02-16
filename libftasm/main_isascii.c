#include <ctype.h>

int	isascii(int c);
int	ft_isascii(int c);

int main_isascii()
{
	for (int i = 0; i < 2555; ++i)
	{
		if(isascii(i) != ft_isascii(i))
		{
			printf("Error for %i.\n", i);
		}
	}
	printf("No error ? So it's OK.\n");
	return 0;
}