/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_original.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mprevot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/26 07:48:08 by mprevot           #+#    #+#             */
/*   Updated: 2017/01/10 16:34:24 by mprevot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <locale.h>
#include <unistd.h>

#include "ft_printf.h"


void printbits21(long v, size_t size) {
  long i; // for C89 compatability
  for(i = --size; i >= 0; i--){
  		ft_putchar('0' + ((v >> i) & 1));
  		if (i % 4 == 0)
  			ft_putchar(' ');
  	};
}

void	test_printf(char *s, ...)
{
	setlocale(LC_ALL, "");
	va_list args;
	va_start(args, s);

	ft_putnbr(vprintf(s, args));


	va_end( args );

}

void	transform(void	*nbr)
{
	((char*)nbr)[0] = 0;
}

int		main(void)
{
	ft_putstr("|");
	ft_printf("%5.x", 0);
	ft_putstr("|");
	/*printf("{%5.s}\n", "(nule)");
	ft_printf("{%5.s}\n", L"(nule)");
	printf("{%5.S}\n", "(nule)");
	ft_printf("{%5.S}\n", L"(nule)");*/
	//ft_printf(str, L"我是一只猫。");
	/*printf("%5.2s is a string\n", "");
	ft_printf("%5.2s is a string\n", "");*/
	/*printf("% 10.5d\n", 4242);
	ft_printf("% 10.5d\n", 4242);*/

	/*ft_printf("%.3S", L"1我是一只猫。");
	ft_printf("\n");
	char str[] = "%.4S";
	printf(str, L"2我是一只猫。");*/
	/*unsigned int test = -1;
	transform(&test);
	printbits21(test, 32);
	exit(0);*/
	//ft_printf("%c wooow", 'z');
	//int a = -1;
	//printf("%C\n", a);

	/*printf("%.5p\n", (void *)0);
	ft_printf("%.5p\n\n", 0);
	printf("%.0p, %.p\n", 0, 0);
	ft_printf("%.0p, %.p\n\n", 0, 0);
	printf("%.1p, %.p\n", 0, 1);
	ft_printf("%.1p, %.p\n", 0, 1);*/
	//printf("%#.4o\n", 4);
	//ft_printf("%#.4o\n", 4);
	//               00042
	/*printf("{%020.5d}\n", 42);
	printf("{%20.5d}\n", 42);
	//00000000000000000042
	printf("{%.20d}\n", 42);
	printf("{%020d}\n", 42);
	printf("{%015.20d}\n", 42);*/

	//En gros on met de 0 à gauche sauf si la précision est supérieure à 1 ET la largeur supérieure à 1.


	//printf("{%010.2d}\n", 9);


	return (0);
}


	/*setlocale(LC_ALL, "");
	printf("%s %S %c\n", "Coucou", L"Gérard !", 'z');
	ft_wputstr(L"Gérard !");
	ft_putchar('\n');*/
	/*unsigned char c[2];*/
	/*110xxxxx 10xxxxxx
	11101001 
	11000011 10101001*/
	/*c[0] = 0xc3;
	c[1] = 0xa9;*/
	//c = 233;
	
	//printf("%s %S %c\n", "Coucou", L"Gérard !", 'z');
	//char *str = "Coucou G\xc3\xa9rard !";
	
	//write(1, str, ft_strlen(str));
	/*printbits(233);*/

	//ft_wputstr(L"Gérard il à manger éééààïlolo");
	// ft_wputstr(L"Gérard il à manger ッ éééààïlolo ￥");
	//printf("𐀀");
	//ft_putnbr(L'😼');
	//ft_wputstr((t_unicode*)L"😼 é 𐀀 éééààïlolo par contre l'ascii marche pas");
	//ft_printf("%S", L"😼 é 𐀀 éééààïlolo par contre l'ascii marche pas");
	//setlocale(LC_ALL, "");
	//printf("%S\n", L"😆 😎 😵 😗 😈 🐻 💓 🌼\n");
	//ft_wputstr
