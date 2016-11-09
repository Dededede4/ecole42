#include <stdio.h>
#include <string.h>

int     ft_count_if(char **tab, int(*f)(char*));

int	isTrue(char *str)
{
	if (strcmp(str, "Knuth") == 0)
		return 1;
	return 0;
}

int		main(void)
{
	char *tab[] = { 
		"Perlis",
	    "Wilkes",
		"Hamming",
		"Minsky",
		"Knuth",
		"McCarthy",
		"Dijkstra",
		"Bachman",
		"Knuth",
		"Newell et Simon",
		0
	};

	int r = ft_count_if(tab, &isTrue);
	printf("%d\n", r);

	return (0);
}
