/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   megaphone.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mprevot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/08 15:32:41 by mprevot           #+#    #+#             */
/*   Updated: 2018/01/09 22:23:57 by mprevot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>

void	yell(char *str)
{
	int		i;

	i = 0;
	while (str[i])
	{
		std::cout << (char)std::toupper(str[i]);
		i++;
	}
}

int		main(int argc, char **argv)
{
	int		i;

	i = 1;
	while (i < argc)
	{
		yell(argv[i]);
		i++;
	}
	if (argc > 1)
		std::cout << std::endl;
	else
		std::cout << "* LOUD AND UNBEARABLE FEEDBACK NOISE *" << std::endl;
	return (0);
}
