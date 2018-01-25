#include "Zombie.hpp"

#include <iostream>
# include <string>

Zombie::Zombie()
{

}

Zombie::~Zombie()
{

}

void Zombie::setName(std::string name)
{
	this->name = name;
}

void Zombie::setType(std::string type)
{
	this->type = type;
}


void Zombie::announce() const
{
	// <name (type)> Braiiiiiiinnnssss...
	std::cout << "<" << this->name << " (" << this->type << ")> Braiiiiiiinnnssss..." << std::endl;
}
