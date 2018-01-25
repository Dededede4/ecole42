/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mprevot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/08 16:23:46 by mprevot           #+#    #+#             */
/*   Updated: 2018/01/08 21:35:55 by mprevot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Contact.class.hpp"
#include <iostream>

int			main(void)
{
	std::string buff;
	std::string input_exit ("EXIT");
	std::string input_add ("ADD");
	std::string input_search ("SEARCH");
	int		i = 0;
	int		y = 0;
	Contact contact[8];

	while(1)
	{
		std::cout << "> ";
		std::getline (std::cin,buff);
		if(input_exit.compare(buff) == 0)
		{
			return (0);
		}
		else if(input_add.compare(buff) == 0 && i < 8)
		{
			contact[i].populate(i);
			i++;
		}
		else if(input_search.compare(buff) == 0)
		{
			while (y < i)
			{
				contact[y].print();
				y++;
			}
			if (i > 0)
			{
				std::cout << "Faites votre choix : ";
				std::getline (std::cin,buff);
				if (buff[0] >= '0' && buff[0] <= '0'+(i-1) && buff[1] == '\0')	
				{
					contact[buff[0] - '0'].printall();
				}
			}
			y = 0;
		}
		else
		{
			std::cout << "input is discarded"  << std::endl;
		}
	}
	return (0);
}
