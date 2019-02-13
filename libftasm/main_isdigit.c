#include <ctype.h>

int	isdigit(int c);
int	ft_isdigit(int c);
int main()
{
	for (int i = 0; i < 2555; ++i)
	{
		if(isdigit(i) != ft_isdigit(i))
		{
			printf("Error for %i.\n", i);
		}
	}
	printf("No error ? So it's OK.\n");
	return 0;
}