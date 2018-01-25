#include "HumanB.hpp"

#include <iostream>
#include <sstream>

HumanB::HumanB(std::string name)
{
	this->name = name;
	
}

HumanB::~HumanB()
{

}

void HumanB::setWeapon(Weapon weapon)
{
	this->w = &weapon;
}

void HumanB::attack() const
{
	std::cout << this->name << " attacks with his " << this->w->getType() << std::endl;
}

std::string const & HumanB::setType(std::string type) const
{
	this->type = type;
}