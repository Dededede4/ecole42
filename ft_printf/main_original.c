/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_original.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mprevot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/26 07:48:08 by mprevot           #+#    #+#             */
/*   Updated: 2017/01/10 13:35:22 by mprevot          ###   ########.fr       */
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

int		main(void)
{
	ft_printf("%C", L'a');
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
