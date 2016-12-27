#include "ft_printf.h"

#include <stdio.h>

int	main(void)
{
	ft_printf("%x %X %o %u %i\n", 6879892, 65456465, 998877552, 65465888, -99999);
	printf("%x %X %o %u %i\n", 6879892, 65456465, 998877552, 65465888, -99999);

	int nbr = 42;
	ft_printf("%p\n", &nbr);
	printf("%p\n", &nbr);
	ft_printf("%s %S %c\n", "Coucou", L"G\x82rard !", 'z');
	printf("%s %S %c\n", "Coucou", L"G\x82rard !", 'z');
	return (0);
}
