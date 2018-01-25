#include "Brain.hpp"

#include <iostream>
#include <sstream>

Brain::Brain()
{

}

Brain::~Brain()
{

}

std::string Brain::identify() const
{
	std::ostringstream address;
	address << (void *)this;
	return address.str();
}
