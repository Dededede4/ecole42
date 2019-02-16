#include <ctype.h>
#include <stdio.h>

int	isalpha(int c);
int	ft_isalpha(int c);
int main_isalpha()
{
	for (int i = 0; i < 2555; ++i)
	{
		if(isalpha(i) != ft_isalpha(i))
		{
			printf("Error for %i.\n", i);
		}
	}
	printf("No error ? So it's OK.\n");
	return 0;
}