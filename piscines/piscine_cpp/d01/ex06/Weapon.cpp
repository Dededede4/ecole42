#include "Weapon.hpp"

#include <iostream>
#include <sstream>

Weapon::Weapon(std::string type)
{
	this->type = type;
}

Weapon::~Weapon()
{

}

std::string const & Weapon::getType() const
{
	return this->type;
}

std::string const & Weapon::setType(std::string type) const
{
	this->type = type;
}