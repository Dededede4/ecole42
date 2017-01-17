#include "ft_printf.h"

#include <stdio.h>
#include <locale.h>

void	test_printf(char *s, ...)
{
	static int printf_no = 0;
	setlocale(LC_ALL, "");
	printf_no++;
	ft_printf("#%zu                  printf(\"%r\", ...);\n", printf_no, (s == NULL) ? "(NULL)" : s);
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
	

	if (strcmp(good_print, bad_print) != 0 || good_return != bad_return)
	{
		ft_printf("Real return (%2i) and print \"%r\"\n", good_return, good_print);
		ft_printf("Your return (%2i) and print \"%r\"\n", bad_return, bad_print);
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
	test_printf("%c wooow", 'z');
	test_printf("%C", L'a');
	test_printf("%C xDD", L'𐀀');

	test_printf("%i", 0);
	test_printf("%d, %d", 245, -952);

	test_printf("%S", L"😼");
	test_printf("miaouu%S", L"😼");
	test_printf("%S", L"miaou😼");
	test_printf("%S\n", L"éaaa\n");
	

	test_printf("Unicode comprises %C entries in the range", 1114111);
	

	
	test_printf("HOY %x %X %o %u %i\n", 6879892, 65456465, 998877552, 65465888, -99999);
	int nbr = 42;
	test_printf("%p", &nbr);
	test_printf("ooo %p\n", &nbr);
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
	test_printf("%-10S", L"");
	test_printf("%-10S", L"blabla");
	test_printf("%-10S", L"blablablab");
	test_printf("%-10S", L"blablablabauieauieauieau");
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
	test_printf("%10u\n", 12);
	test_printf("%010u\n", 12);

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


	// les tests qui foirent
	test_printf("%-10x", 42);
	test_printf("%-15x", 542);
	test_printf("%c", 0);
	test_printf("%C", 0);
	test_printf("%hhC, %hhC", 'a', L'米');
	test_printf("{%-10d}", 42);
	test_printf("{%Z}", 123);
	test_printf("{%-15Z}", 123);
	test_printf("%#o", 0);
	test_printf("%+c", 0);
	test_printf("% u", 9999);
	test_printf("%.c", 0);
	//test_printf(NULL);


	test_printf("%#.4o\n", 4);
	test_printf("%.4d", 42);
	test_printf("%.4d", 424242);
	test_printf("%.4o", 424242);
	test_printf("test %c test", 0);
	test_printf("%S", L"");
	test_printf("%S%S%S%S%S%S%S%S%S%S%S%S%S%S%S%S%S%S%S%S%S%S%S%S ",
	L"Α α", L"Β β", L"Γ γ", L"Δ δ", L"Ε ε", L"Ζ ζ", L"Η η", L"Θ θ", L"Ι ι", L"Κ κ", L"Λ λ", L"Μ μ",
	L"Ν ν", L"Ξ ξ", L"Ο ο", L"Π π", L"Ρ ρ", L"Σ σ", L"Τ τ", L"Υ υ", L"Φ φ", L"Χ χ", L"Ψ ψ", L"Ω ω");
	test_printf("%S%S%S%S%S%S%S%S%S%S%S%S%S%S%S%S%S%S%S%S%S%S%S%S%S",
	L"Α α", L"Β β", L"Γ γ", L"Δ δ", L"Ε ε", L"Ζ ζ", L"Η η", L"Θ θ", L"Ι ι", L"Κ κ", L"Λ λ", L"Μ μ",
	L"Ν ν", L"Ξ ξ", L"Ο ο", L"Π π", L"Ρ ρ", L"Σ σ", L"Τ τ", L"Υ υ", L"Φ φ", L"Χ χ", L"Ψ ψ", L"Ω ω", L"");
	test_printf("%o, %ho, %hho", -42, -42, -42);
	test_printf("%c", 200);
	test_printf("%C", 200);
	test_printf("% p|%+p", 42, 42);
	test_printf("%.5i\n%.5i\n", 42, 424242424);
	test_printf("%#x", 0);
	test_printf("%.x", 0);
	test_printf("%#.x, %#.0x", 0, 0);
	test_printf("%.1x", 0);
	test_printf("wa %.2x", 0);
	test_printf("%.0p, %.p", 0, 0);
	test_printf("%15.4o", 42);
	test_printf("%.4s", "42 is the answer");
	test_printf("%15.4d", 42);
	test_printf("{%0-3u}", 0);
	test_printf("{%0-3d}", 0);
	test_printf("{%03u}", 0);
	test_printf("{%03d}", 0);
	test_printf("{% c}", 0);
	test_printf("%+o", 0);
	test_printf("%#X", 42);
	test_printf("{%0c}", 'z');
	test_printf("{%3c}", 'z');
	test_printf("{%.3c}", 'z');
	test_printf("{%03c}", 'z');
	test_printf("{%-03c}", 'z');
	test_printf("{%03C}", 0);
	test_printf("{%03c}", 0);
	test_printf("{%03c}", 1);
	test_printf("{%10d}", -42);
	test_printf("%hhC, %hhC", 0, L'米');
	test_printf("%p", 0);

	test_printf("{%5p}", 0);
	test_printf("{%010d}", -42);
	test_printf("{% 03d}", 0);
	test_printf("%15.4d", 424242);
	test_printf("%15.4o", 424242);
	test_printf("%4.15s", "I am 42");
	test_printf("%.5p", 0);
	test_printf("%#.o, %#.0o", 0, 0);
	test_printf("%#.o", 42);

	// Errors cases

	// Alway return -1 now.
	test_printf("Unicode comprises %C code points in the range", 1114112);
	test_printf("test");
	test_printf("%C", -1);
	test_printf("0dur %C dur", 2147483646);
	test_printf("dur %C dur", 2147483647);
	test_printf("max +1 utf8 4-bytes is %C", 1114111 + 1);
	test_printf("Unicode values %C because is signed", -1);
	test_printf("Invalides str %C through %C", 55296, 57343);


	

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
