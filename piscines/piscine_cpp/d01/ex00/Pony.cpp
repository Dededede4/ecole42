#include "Pony.hpp"

#include <iostream>

Pony::Pony() 
{
	std::cout << "A pony is born" << std::endl;
}


Pony::~Pony() 
{
	std::cout << "A pony is died" << std::endl;
}
