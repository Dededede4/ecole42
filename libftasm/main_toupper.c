#include <ctype.h>
#include <stdio.h>

int	toupper(int c);
int	ft_toupper(int c);
int main_toupper()
{
	for (int i = 0; i < 2555; ++i)
	{
		if(toupper(i) != ft_toupper(i))
		{
			printf("Error for %i.\n", i);
		}
	}
	printf("No error ? So it's OK.\n");
	return 0;
}