#ifndef VICTIM_HPP
# define VICTIM_HPP

#include <iostream>

class Victim {

public:
	Victim(std::string name);
	Victim(Victim const & src);
	~Victim(void);

	Victim & operator=( Victim const & rhs);

	virtual void getPolymorphed() const;
	std::string getName() const;

protected :
	std::string	name;
};

std::ostream & operator<<( std::ostream & o, Victim const & rhs );

#endif