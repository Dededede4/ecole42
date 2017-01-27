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
	test_printf("hello tests");
	test_printf("test test test 		test lol");
	test_printf("\n");
	test_printf("");
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
	test_printf("%");
	test_printf("%%");
	test_printf("%%%%%%%%");
	test_printf("%%aa%%cc%%000%%");
	test_printf("a%0cc%%000%%");
	test_printf("a%1cc%%000%%");
	test_printf("a%2cc%%000%%");
	test_printf("%-10S", L"");
	test_printf("%-10S", L"blabla");
	test_printf("%-10S", L"blablablab");
	test_printf("%-10S", L"blablablabauieauieauieau");
	test_printf("%-10s| :)\n", "hey");
	test_printf("%10s| :)\n", "hey");
	test_printf("%10s %10S %10c\n", "Coucou", L"aaa", 'z');
	test_printf("%-10s %-10S %-10c\n", "Coucou", L"aaa", 'z');
	test_printf("%-10s %-10S %-10c\n", "Coucou", L"aaa", 'z');
	test_printf("%+i %+i % i % i\n", 321, -321, 321, -321);
	test_printf("%#o\n", 12);
	test_printf("%10i\n", 12);
	test_printf("%10u\n", 12);
	test_printf("%010u\n", 12);
	test_printf("%05s\n", "pouet");
	test_printf("%.12d\n", 42);
	test_printf("%.15x\n", 9584);
	test_printf("%.5i\n", 42);
	test_printf("%05i\n", 42);
	test_printf("%.10s\n", "pouet");
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
	test_printf("%15.4d", 4);
	test_printf("%15.4d", 424242);
	test_printf("%15.4o", 424242);
	test_printf("%4.15s", "I am 42");
	test_printf("%.5p", 0);
	test_printf("%#o", 0);
	test_printf("%.o", 0);
	test_printf("%#.o", 32);
	test_printf("%#.o, %#.0o", 0, 0);
	test_printf("%#.o", 42);
	test_printf("{%30S}", L"test");
	test_printf("{%30S}", L"étest");
	test_printf("{%30S}", L"ééééééééééééééééé");
	test_printf("{%30S}", L"éééééééééééééééééééééééééééééé");
	test_printf("{%30S}", L"我是一只猫。");
	test_printf("{%030S}", L"我是一只猫。");
	test_printf("{%10.5d}\n", 9);
	test_printf("{%03.2d}", 9);
	test_printf("{%03.5d}", 9);
	test_printf("{%03.10d}", 9);
	test_printf("{%03.2d}", 0);
	test_printf("{%020.8d}\n", 42);
	test_printf("{%020.5d}\n", 42);
	test_printf("{%20.5d}\n", 42);
	test_printf("{%.20d}\n", 42);
	test_printf("{%020d}\n", 42);
	test_printf("{%015.20d}\n", 42);
	test_printf("{%-020.8d}\n", 42);
	test_printf("{%-020.5d}\n", 42);
	test_printf("{%-20.5d}\n", 42);
	test_printf("{%-.20d}\n", 42);
	test_printf("{%-020d}\n", 42);
	test_printf("{%-015.20d}\n", 42);
	test_printf("{%10.5u}\n", 9);
	test_printf("{%03.2u}", 9);
	test_printf("{%03.5u}", 9);
	test_printf("{%03.10u}", 9);
	test_printf("{%03.2u}", 0);
	test_printf("{%020.8u}\n", 42);
	test_printf("{%020.5u}\n", 42);
	test_printf("{%20.5u}\n", 42);
	test_printf("{%.20u}\n", 42);
	test_printf("{%020u}\n", 42);
	test_printf("{%015.20u}\n", 42);
	test_printf("{%-020.8u}\n", 42);
	test_printf("{%-020.5u}\n", 42);
	test_printf("{%-20.5u}\n", 42);
	test_printf("{%-.20u}\n", 42);
	test_printf("{%-020u}\n", 42);
	test_printf("{%-015.20u}\n", 42);
	test_printf("%.1p, %.p\n", 0, 1);
	test_printf("%.d, %.0d", 0, 0);
	test_printf("%.4s", "yaaaaaaaaa");
	test_printf("%.4S", L"我是一只猫。");
	test_printf("%.7S", L"我是一只猫。");
	test_printf("%.0p, %.p", 0, 0);
	test_printf("{%05p}", 0);
	test_printf("%15.4s", "I am 42");
	test_printf("%2.9p", 1234);
	test_printf("%.0%");
	test_printf("%#08x", 42);
	test_printf("%5.2s is a string", "this");
	test_printf("%10s is a string", "");
	test_printf("%5.2s is a string", "");
	test_printf("%-5.2s is a string", "this");
	test_printf("% 10.5d", 4242);
	test_printf("%+10.5d", 4242);
	test_printf("%10.5d", -4242);
	test_printf("%03.2d", -1);
	test_printf("%.5C", 0);
	test_printf("%.5C", L'a');
	test_printf("%.5S", L"a");
	test_printf("%15.4s", "42");
	test_printf("%.10d", -42);
	test_printf("%15.4S", L"ééééééééééé");
	test_printf("%15.4S", L"éééééééééééééééééééé");
	test_printf("%15.4S", L"我是一只猫。");
	test_printf("%4.4S", L"我是一只猫。");
	test_printf("%4.1S", L"é");
	test_printf("%4.2S", L"é");
	test_printf("%4.3S", L"éé");
	test_printf("%15.4s", "42 is the answer");
	test_printf("%4.15S", L"我是一只猫。");
	test_printf("%4.S", L"我是一只猫。");
	test_printf("%4.1S", L"Jambon");
	test_printf("%%   %", "test");
	test_printf("%4.s", "42");
	test_printf("{%05.s}", 0);
	test_printf("{%05.s}\n", "(nule)");
	test_printf("{%5.s}\n", "(nule)");
	test_printf("{%5s}\n", "(nule)");
	test_printf("{%.5s}\n", "(nule)");
	test_printf("{%05.s}\n", 0);
	test_printf("{%5.s}\n", 0);
	test_printf("{%0.s}\n", 0);
	test_printf("{%s}", 0);
	test_printf("{%S}", 0);
	test_printf("{% s}", NULL);
	test_printf("{%05.%}", 0);
	test_printf("{%05.Z}", 0);
	test_printf("%C%C%C%C%C%C%C%C%C%C%C%C%C%C%C%C%C%C%C%C \
	%C%C%C%C%C%C%C%C%C%C%C%C%C%C%C%C%C%C%C%C%C%C%C%C%C%C%C%C%C%C%C%C%C%C%C%C%C%C%C\
	%C%C%C%C%C%C%C%C%C%C%C%C%C%C%C%C%C%C%C%C%C%C%C%C%C%C%C%C%C%C%C%C%C%C",
	' ', '!', '"', '#', '$', '%', '&', '\'', '(', ')', '*', '+', ',', '-',
	'.', '/', '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', ':', ';',
	'<', '=', '>', '?', '@', 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I',
	'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W',
	'X', 'Y', 'Z', '[', '\\', ']', '^', '_', '`', 'a', 'b', 'c', 'd', 'e',
	'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's',
	't', 'u', 'v', 'w', 'x', 'y', 'z', '{', '|', '}');
	test_printf("%5.x", 0);
	test_printf("%5.x", 1);
	test_printf("@moulitest: %5.x %5.0x", 0, 0);
	test_printf("@moulitest: %5.o %5.0o", 0, 0);
	test_printf("@moulitest: %.d %.0d", 42, 43);
	test_printf("@moulitest: %5.d %5.0d", 0, 0);
	// Comportements indéfini
	/*test_printf("%ll#x", 9223372036854775807);
	test_printf("%5+d", 42);
	test_printf("%5+d", -42);
	test_printf("%-5+d", 42);
	test_printf("%-5+d", -42);
	test_printf("%zhd", "4294967296");
	test_printf("%jzd", "9223372036854775807");
	test_printf("%jhd", "9223372036854775807");
	test_printf("%lhl", "9223372036854775807");
	test_printf("%lhlz", "9223372036854775807");
	test_printf("%zj", "9223372036854775807");
	test_printf("%lhh", "2147483647");
	test_printf("%hhld", "128");
	test_printf("@main_ftprintf: %####0000 33..1..#00d\n", 256);
	test_printf("@main_ftprintf: %####0000 33..1d", 256);
	test_printf("@main_ftprintf: %###-#0000 33...12..#0+0d", 256);*/


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
