/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Contact.class.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mprevot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/08 22:29:44 by mprevot           #+#    #+#             */
/*   Updated: 2018/01/08 22:29:46 by mprevot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Contact.class.hpp"

#include <iostream>

void Contact::populate(int index) 
{
	this->index = std::to_string(index);

	std::cout << "first name : ";
	std::getline (std::cin,this->first_name);
	std::cout << std::endl;

	std::cout << "last name : ";
	std::getline (std::cin,this->last_name);
	std::cout << std::endl;

	std::cout << "nickname : ";
	std::getline (std::cin,this->nickname);
	std::cout << std::endl;

	std::cout << "login : ";
	std::getline (std::cin,this->login);
	std::cout << std::endl;

	std::cout << "postal address : ";
	std::getline (std::cin,this->postal_address);
	std::cout << std::endl;

	std::cout << "email address : ";
	std::getline (std::cin,this->email_address);
	std::cout << std::endl;

	std::cout << "phone number : ";
	std::getline (std::cin,this->phone_number);
	std::cout << std::endl;

	std::cout << "birthday date : ";
	std::getline (std::cin,this->birthday_date);
	std::cout << std::endl;

	std::cout << "favorite meal : ";
	std::getline (std::cin,this->favorite_meal);
	std::cout << std::endl;

	std::cout << "underwear color : ";
	std::getline (std::cin,this->underwear_color);
	std::cout << std::endl;

	std::cout << "darkest secret : ";
	std::getline (std::cin,this->darkest_secret);
	std::cout << std::endl;
}

void Contact::printlimt(std::string str) const
{
	int i = 0;
	size_t size = str.size();
	int spaces = 10 - size;

	while (i < spaces)
	{
		std::cout << " ";
		i++;
	}
	i = 0;
	while (str[i] && i < 10)
	{
		if (i == 9)
			std::cout << ".";
		else
			std::cout << (char)str[i];
		i++;
	}

}


void Contact::print(void) const
{
	this->printlimt(this->index);
	std::cout << "|";
	this->printlimt(this->first_name);
	std::cout << "|";
	this->printlimt(this->last_name);
	std::cout << "|";
	this->printlimt(this->nickname);
	std::cout << std::endl;
}

void Contact::printall(void) const
{
	std::cout << "Index : " << this->index << std::endl;

	std::cout << "first name : " << this->first_name << std::endl;

	std::cout << "last name : " << this->last_name << std::endl;

	std::cout << "nickname : " << this->nickname << std::endl;

	std::cout << "login : " << this->login << std::endl;

	std::cout << "postal address : " << this->postal_address << std::endl;

	std::cout << "email address : " << this->email_address << std::endl;

	std::cout << "phone number : " << this->phone_number << std::endl;

	std::cout << "birthday date : " << this->birthday_date << std::endl;

	std::cout << "favorite meal : " << this->favorite_meal << std::endl;

	std::cout << "underwear color : " << this->underwear_color << std::endl;

	std::cout << "darkest secret : " << this->darkest_secret << std::endl;
}
