#include <iostream>
#include "Peon.hpp"

Peon::Peon(std::string name) : Victim(name)
{
	std::cout << "Zog zog." << std::endl;
}

Peon::Peon(Peon const & src) : Victim(src){
	*this = src;
}

Peon::~Peon(void) {
	std::cout << "Bleuark..." << std::endl;
}

Peon & Peon::operator=( Peon const & rhs) {
	if (this != &rhs)
	{
		this->name = rhs.name;
	}
	return *this;
}

void Peon::getPolymorphed() const {
	std::cout << this->getName() << " has been turned into a pink pony !" << std::endl;
}

std::ostream & operator<<( std::ostream & o, Peon const & rhs ) {
	o << "I'm " << rhs.getName() << " and I like otters !" << std::endl;
	return o;
}



<?php

class Victime {

}
