#include <ctype.h>

int	isprint(int c);
int	ft_isprint(int c);

int main_isprint()
{
	for (int i = 0; i < 2555; ++i)
	{
		if(isprint(i) != ft_isprint(i))
		{
			printf("Error for %i.\n", i);
		}
	}
	printf("No error ? So it's OK.\n");
	return 0;
}