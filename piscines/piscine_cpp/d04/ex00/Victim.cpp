#include <iostream>
#include "Victim.hpp"

Victim::Victim(std::string name) : 

	name(name)
{
	std::cout << "Some random victim called " << name << " just popped !" << std::endl;
}

Victim::Victim(Victim const & src) {
	*this = src;
}

Victim::~Victim(void) {
	std::cout << "Victim " << name << " just died for no apparent reason !" << std::endl;
}

Victim & Victim::operator=( Victim const & rhs) {
	if (this != &rhs)
	{
		this->name = rhs.name;
	}
	return *this;
}

std::ostream & operator<<( std::ostream & o, Victim const & rhs ) {
	o << "I'm " << rhs.getName() << " and I like otters !" << std::endl;
	return o;
}

void Victim::getPolymorphed() const {
	std::cout << name << " has been turned into a little sheep !" << std::endl;
}

std::string Victim::getName() const {
	return name;
}