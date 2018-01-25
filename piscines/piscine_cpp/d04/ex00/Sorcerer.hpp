#ifndef SORCERER_HPP
# define SORCERER_HPP

#include <iostream>
#include "Victim.hpp"

class Sorcerer {

public:
	Sorcerer(std::string name, std::string title);
	Sorcerer(Sorcerer const & src);
	~Sorcerer(void);

	Sorcerer & operator=( Sorcerer const & rhs);

	void polymorph(Victim const & victim) const;

	std::string getName() const;
	std::string getTitle() const;

private :
	std::string	name;
	std::string title;
};

std::ostream & operator<<( std::ostream & o, Sorcerer const & rhs );

#endif