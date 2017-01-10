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
	good_return = vprintf(s, args);
	fflush(stdout);
	write(1, "\0", 1);
	t = read(p[0], good_print, 1023);
	good_print[t] = '\0';
	dup2(out, 1);	
	va_end( args );

	va_start(args, s);
	out = dup(1);
        pipe(p);
        dup2(p[1], 1);
        bad_return = ft_vprintf(s, args);
		fflush(stdout);
		write(1, "\0", 1);
        bad_print[read(p[0], bad_print, 1023)] = '\0';
	dup2(out, 1);
	va_end( args );
	

	if (memcmp(good_print, bad_print, ft_strlen(good_print)) != 0 || good_return != bad_return)
	{
		ft_printf("#%zu                  printf(\"%r\", ...);\n", printf_no, s);
		ft_printf("Real return (%i) and print \"%r\"\n", good_return, good_print);
		ft_printf("Your return (%i) and print \"%r\"\n", bad_return, bad_print);
		ft_printf("Difference is %i.\n\n", strcmp(good_print, bad_print));
	}
}

int	main(void)
{
	// Basic usage
	test_printf("hello tests");
	test_printf("test test test 		test lol");
	test_printf("\n");
	test_printf("");

	// Vous devez gérer les conversions suivantes : sSpdDioOuUxXcC
	test_printf("%C", L'a');
	test_printf("%C", L'𐀀');

	test_printf("%d, %d", 245, -952);

	test_printf("%S\n", L"éaaa\n");
	test_printf("HOY %x %X %o %u %i\n", 6879892, 65456465, 998877552, 65465888, -99999);

	int nbr = 42;
	test_printf("%p\n", &nbr);
	test_printf("%S\n", L"é");
	test_printf("%S", L"ooo ❤ ☀ ☆ ☂ ☻ ♞ ☯ ☭ ☢ € dddd");
	test_printf("%s %c\n", "Coucou", 'z');

	int nbr2 = 99;
	test_printf("666%p\n", &nbr2);

	// Vous devez gérer le %%
	test_printf("%");
	test_printf("%%");
	test_printf("%%%%%%%%");
	test_printf("%%aa%%cc%%000%%");
	test_printf("a%0cc%%000%%");

	// Vous devez gérer les flags #0-+ et espace
	// Pour s
	test_printf("%-10s| :)\n", "hey");
	test_printf("%10s| :)\n", "hey");
	test_printf("%10s %10S %10c\n", "Coucou", L"aaa", 'z');
	test_printf("%-10s %-10S %-10c\n", "Coucou", L"aaa", 'z');
	test_printf("%-10s %-10S %-10c\n", "Coucou", L"aaa", 'z');

	// pour i
	test_printf("%+i %+i % i % i\n", 321, -321, 321, -321);

	// pour o
	test_printf("%#o\n", 12);

	// Vous devez gérer la taille minimum du champ
	// pour i
	test_printf("%10i\n", 12);

	//pour s
	test_printf("%05s\n", "pouet");


	// Vous devez gérer les flags hh h l ll j z

	// Vous devez gérer la précision
	// pour d
	test_printf("%.12d\n", 42);

	// pour x
	test_printf("%.15x\n", 9584);

	// pour i
	test_printf("%.5i\n", 42);
	test_printf("%05i\n", 42);

	// pour s
	test_printf("%.10s\n", "pouet");
	

	

	

	/*unsigned int unicode = L'a';*/
	/*while (unicode < (unsigned int)-1)
		test_printf("%C", unicode++);*/

	/*int *strunicode = L"a";
	while (unicode < (unsigned int)-1)
	{
		*strunicode = unicode++;
		test_printf("%S", strunicode);
	}*/

	// Bonus :
	//unsigned int nbr3 = 42;
	//test_printf("%b\n", nbr3);

	return (0);
}
