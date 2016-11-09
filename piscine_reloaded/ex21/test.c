#include <stdio.h>

int     *ft_range(int min, int max);

int		main()
{
	int 	min = -3;
	int		max = 20;
	int		loops = max - min;
	int		*tab = ft_range(min, max);
	int		i = 0;

	while (i < loops){
		printf("%d\n", tab[i]);
		i++;
	}
}
