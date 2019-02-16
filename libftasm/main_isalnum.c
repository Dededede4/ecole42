#include <ctype.h>
#include <stdio.h>

int	isalnum(int c);
int	ft_isalnum(int c);

int main_isalnum()
{
	for (int i = 0; i < 2555; ++i)
	{
		if(isalnum(i) != ft_isalnum(i))
		{
			printf("Error for %i.\n", i);
		}
	}
	printf("No error ? So it's OK.\n");
	return 0;
}