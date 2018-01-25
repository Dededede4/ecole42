#ifndef ZOMBIE_HORDE_HPP
# define ZOMBIE_HORDE_HPP

#include <string>
#include "Zombie.hpp"

class ZombieHorde {
	public:
		ZombieHorde(int N);
		void announce() const;
	private:
		Zombie *zombies;
		int size;
};
#endif
