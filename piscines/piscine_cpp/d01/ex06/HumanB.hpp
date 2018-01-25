#ifndef HUMAN_B_HPP
# define HUMAN_B_HPP

# include <string>
#include "Weapon.hpp"

class HumanB {
	public:
		HumanB(std::string name);
		~HumanB();
		void setWeapon(Weapon weapon);
		void attack() const;
		void setType(std::string type);
	private:
		std::string name;
		Weapon *w;
};
#endif