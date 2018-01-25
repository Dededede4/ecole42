#ifndef ZAZ_HPP
# define ZAZ_HPP

#include <iostream>
#include "Victim.hpp"

class Zaz : public Victim {

public:
	Zaz(std::string name);
	Zaz(Zaz const & src);
	~Zaz(void);

	Zaz & operator=( Zaz const & rhs);

	virtual void getPolymorphed() const;
};

#endif