#include <stdio.h>

void    ft_foreach(int *tab, int length, void(*f)(int));

void putnbr(int nb)
{
	printf("%d\n", nb);
}

int		main(void)
{
	int tab[4];
	tab[0] = 42;
	tab[1] = -50;
   	tab[2] = 12;
	tab[3] = 40000;

	ft_foreach(tab, 4, &putnbr);
	return (0);
}
