#ifndef HUMAN_A_HPP
# define HUMAN_A_HPP

# include <string>
#include "Weapon.hpp"

class HumanA {
	public:
		HumanA(std::string name, Weapon w2);
		~HumanA();
		void attack() const;
		void setType(std::string type);
	private:
		std::string name;
		Weapon *w;
		std::string type;
};
#endif