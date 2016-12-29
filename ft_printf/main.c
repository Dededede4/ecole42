#include "ft_printf.h"

#include <stdio.h>

int	main(void)
{
	ft_printf("HEY %x %X %o %u %i\n", 6879892, 65456465, 998877552, 65465888, -99999);
	printf("HOY %x %X %o %u %i\n", 6879892, 65456465, 998877552, 65465888, -99999);

	int nbr = 42;
	ft_printf("%p\n", &nbr);
	printf("%p\n", &nbr);
	
	ft_printf("%s %S %c\n", "Coucou", L"G\x82rard !", 'z');
	printf("%s %S %c\n", "Coucou", L"G\x82rard !", 'z');

	ft_printf("%.12d\n", 42);
	printf("%.12d\n", 42);

	ft_printf("%.15x\n", 9584);
	printf("%.15x\n", 9584);

	int nbr2 = 99;
	ft_printf("%p\n", &nbr2);
	printf("%p\n", &nbr2);

	unsigned int nbr3 = 42;
	ft_printf("%b\n", nbr3);

	ft_printf("%#o\n", 12);
	printf("%#o\n", 12);

	printf("%-10s| :)\n", "hey");
	ft_printf("%-10s| :)\n", "hey");
	printf("%10s| :)\n", "hey");
	ft_printf("%10s| :)\n", "hey");

	ft_printf("%10s %10S %10c\n", "Coucou", L"G\x82rard !", 'z');
	printf("%10s %10S %10c\n", "Coucou", L"G\x82rard !", 'z');

	ft_printf("%-10s %-10S %-10c\n", "Coucou", L"G\x82rard !", 'z');
	printf("%-10s %-10S %-10c\n", "Coucou", L"G\x82rard !", 'z');

	ft_printf("%-10s %-10S %-10c\n", "Coucou", L"G\x82rard !", 'z');
	printf("%-10s %-10S %-10c\n", "Coucou", L"G\x82rard !", 'z');

	ft_printf("%+i %+i % i % i\n", 321, -321, 321, -321);
	printf("%+i %+i % i % i\n", 321, -321, 321, -321);

	ft_printf("\n");
	printf("\n");

	int s1;
	int s2;

	s1 = printf("%10i\n", 12);
	s2 = ft_printf("%10i\n", 12);

	printf("%d, %d\n", s1, s2);
	
	//printf("%i");

	/*printf("%.5i\n", 42);
	printf("%05i\n", 42);

	printf("%.10s\n", "pouet");
	//printf("%05s\n", "pouet");*/

	return (0);
}
