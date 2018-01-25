#include "Zombie.hpp"

#include <iostream>
# include <string>

Zombie::Zombie(std::string name, std::string type) 
{
	this->name = name;
	this->type = type;
}

void Zombie::announce() const
{
	// <name (type)> Braiiiiiiinnnssss...
	std::cout << "<" << this->name << " (" << this->type << ")> Braiiiiiiinnnssss..." << std::endl;
}
