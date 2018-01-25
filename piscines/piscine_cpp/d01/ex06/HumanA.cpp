#include "HumanA.hpp"

#include <iostream>
#include <sstream>
#include "Weapon.hpp"

HumanA::HumanA(std::string name, Weapon w2)
{
	this->name = name;
	this->w = &w2;
}

HumanA::~HumanA()
{

}

void HumanA::attack() const
{
	std::cout << this->name << " attacks with his " << this->w->getType() << std::endl;
}

void HumanA::setType(std::string type)
{
	this->type = type;
}