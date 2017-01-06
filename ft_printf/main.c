#include "ft_printf.h"

#include <stdio.h>
#include <locale.h>

void	test_printf(char *s, ...)
{
	static int printf_no = 0;
	setlocale(LC_ALL, "");
	printf_no++;
	ft_printf("go");
	va_list args;
	va_start(args, s);

	int 	good_return;
        char    good_print[1024];
	
	int 	bad_return;
	char	bad_print[1024];
	
	int	p[2];
	int	out;
	
	int 	t;
	
	out = dup(1);
	pipe(p);
	dup2(p[1], 1);
	good_return = printf(s, args);
	fflush(stdout);
	t = read(p[0], good_print, 1023);
	if (printf_no == 3)
		exit(0);
	good_print[t] = '\0';
	dup2(out, 1);	
	
	out = dup(1);
        pipe(p);
        dup2(p[1], 1);

        bad_return = ft_printf(s, args);
        bad_print[read(p[0], bad_print, 1023)] = '\0';
	dup2(out, 1);

	va_end( args );

	if (strcmp(good_print, bad_print) != 0 || good_return != bad_return)
	{
		ft_printf("#%i                  printf(\"%r\", ...);\n", printf_no, s);
		ft_printf("Real return (%i) and print \"%r\"\n", good_return, good_print);
		ft_printf("Your return (%i) and print \"%r\"\n\n", bad_return, bad_print);
	}
}

int	main(void)
{
	
	test_printf("HOY %x %X %o %u %i\n", 6879892, 65456465, 998877552, 65465888, -99999);
	
	int nbr = 42;
	test_printf("%p\n", &nbr);
	
	test_printf("%S\n", L"é");

	//test_printf("%s %S %c\n", "Coucou", L"G\x82rard !", 'z');
	test_printf("%.12d\n", 42);

	test_printf("%.15x\n", 9584);

	int nbr2 = 99;
	test_printf("%p\n", &nbr2);

	unsigned int nbr3 = 42;
	test_printf("%b\n", nbr3);

	test_printf("%#o\n", 12);

	test_printf("%-10s| :)\n", "hey");
	test_printf("%10s| :)\n", "hey");
	//test_printf("%10s %10S %10c\n", "Coucou", L"Gérard !", 'z');
	//test_printf("%-10s %-10S %-10c\n", "Coucou", L"G\x82rard !", 'z');
	//test_printf("%-10s %-10S %-10c\n", "Coucou", L"G\x82rard !", 'z');
	test_printf("%+i %+i % i % i\n", 321, -321, 321, -321);
	test_printf("%10i\n", 12);

	int s1 = 245;
	int s2 = -952;
	test_printf("%d, %d", s1, s2);
	//printf("%i");
/*
	printf("%.5i\n", 42);
	printf("%05i\n", 42);

	printf("%.10s\n", "pouet");
	printf("%05s\n", "pouet");*/

	return (0);
}
