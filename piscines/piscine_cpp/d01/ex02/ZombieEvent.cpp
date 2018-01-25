#include "ZombieEvent.hpp"
#include "Zombie.hpp"
#include <string>

void ZombieEvent::setZombieType(std::string type)
{
	this->type = type;
}

Zombie *ZombieEvent::newZombie(std::string name) const
{
	return new Zombie(name, this->type);
} 

Zombie *ZombieEvent::randomChump(void) const
{
	std::string names[11] = {"mprevot", "obama", "george", "alexandre", "myriam", "sarah", "orelsan", "misterv", "simone", "norman"};

	return new Zombie(names[rand() % 10], this->type);
}


