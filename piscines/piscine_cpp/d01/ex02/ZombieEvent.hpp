#ifndef ZOMBIE_EVENT_HPP
# define ZOMBIE_EVENT_HPP

#include <string>
#include "Zombie.hpp"

class ZombieEvent {
	public:
		void setZombieType(std::string type);
		Zombie* newZombie(std::string name) const;
		Zombie *randomChump(void) const;
		void announce() const;
	private:
		std::string type;
};
#endif