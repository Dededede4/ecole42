#include <stdio.h>

int     *ft_range(int min, int max);

int		main()
{
	int 	min = -42;
	int		max = 42;
	int		loops = max - min - 1;
	int		*tab = ft_range(-42, 42);
	int		i = 0;

	while (i < loops){
		printf("%d\n", tab[i]);
		i++;
	}
}
