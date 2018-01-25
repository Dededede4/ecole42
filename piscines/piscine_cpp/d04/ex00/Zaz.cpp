#include <iostream>
#include "Zaz.hpp"

Zaz::Zaz(std::string name) : Victim(name)
{
	std::cout << name << " sort du bocal." << std::endl;
}

Zaz::Zaz(Zaz const & src) : Victim(src){
	*this = src;
}

Zaz::~Zaz(void) {
	std::cout << "OMG je suis fait mprevotté 😵" << std::endl;
}

Zaz & Zaz::operator=( Zaz const & rhs) {
	if (this != &rhs)
	{
		this->name = rhs.name;
	}
	return *this;
}

void Zaz::getPolymorphed() const {
	std::cout << this->getName() << " has been turned into a facebook employee !" << std::endl;
}

std::ostream & operator<<( std::ostream & o, Zaz const & rhs ) {
	o << "I'm " << rhs.getName() << " and JE VOUS DONNE DES CONSIGNES CHIANTES !" << std::endl;
	return o;
}