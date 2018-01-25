#include <iostream>
#include "Sorcerer.hpp"

Sorcerer::Sorcerer(std::string name, std::string title) : 

	name(name)
	,title(title)
{
	std::cout << name << ", " << title << ", is born !" << std::endl;
}

Sorcerer::Sorcerer(Sorcerer const & src) {
	*this = src;
}

Sorcerer::~Sorcerer(void) {
	std::cout << name << ", " << title << ", is dead. Consequences will never be the same !" << std::endl;
}

Sorcerer & Sorcerer::operator=( Sorcerer const & rhs) {
	(void)rhs;
	if (this != &rhs)
	{
		this->name = rhs.name;
		this->title = rhs.title;
	}
	return *this;
}

std::ostream & operator<<( std::ostream & o, Sorcerer const & rhs ) {
	o << "I am " << rhs.getName() << ", " << rhs.getTitle() <<", and I like ponies !" << std::endl;
	return o;
}

void Sorcerer::polymorph(Victim const & victim) const {
	victim.getPolymorphed();
}

std::string Sorcerer::getName() const {
	return name;
}

std::string Sorcerer::getTitle() const {
	return title;
}