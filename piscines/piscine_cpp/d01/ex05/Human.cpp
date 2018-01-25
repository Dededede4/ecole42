#include "Human.hpp"
#include "Brain.hpp"

#include <iostream>
# include <string>

Human::Human()
{
}

Human::~Human()
{
	//delete this->Brain;
}

std::string Human::identify() const
{
	return this->Brain.identify();
}

Brain const & Human::getBrain()
{
	return this->Brain;
}