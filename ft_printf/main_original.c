/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_original.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mprevot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/26 07:48:08 by mprevot           #+#    #+#             */
/*   Updated: 2017/01/04 12:01:51 by mprevot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "ft_printf.h"

#include <locale.h>

void printbits(int v);

void	test2(char *s, ...)
{
	va_list args;
	va_start(args, s);
	char nbr = va_arg(args, int);
	ft_putnbr((int)nbr); // Affiche -32 (pas normal)
	ft_putchar('\n');
	(void)nbr;	
	va_end(args);
}

void	test1(char *s, ...)
{
	va_list args;
	va_start(args, s);
	test2(s, args);
	va_end(args);

	char nbr = va_arg(args, int);
	ft_putnbr((int)nbr); // Affiche 97 (normal)
	va_end(args);
}

int		main(void)
{
	test1("useless", 'a');
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