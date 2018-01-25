#ifndef HUMAN_HPP
# define HUMAN_HPP

# include <string>
#include "Brain.hpp"

class Human {
	public:
		std::string identify() const;
		Brain const &getBrain();
		Human();
		~Human();
	private:
		Brain Brain;
};
#endif