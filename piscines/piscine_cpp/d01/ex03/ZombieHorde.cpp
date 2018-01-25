#include "ZombieHorde.hpp"
#include "Zombie.hpp"
#include <string>

ZombieHorde::ZombieHorde(int N)
{
	int i = 1;
	N++;
	this->zombies = new Zombie[N];
	this->size = N;

	std::string names[11] = {"mprevot", "obama", "george", "alexandre", "myriam", "sarah", "orelsan", "misterv", "simone", "norman"};

	while (i < N)
	{
		this->zombies[i].setName(names[rand() % 9]);
		this->zombies[i].setType("Member of the order");
		i++;
	}
}

void	ZombieHorde::announce() const
{
	int i = 1;

	while (i < this->size)
	{
		this->zombies[i].announce();
		i++;	
	}
}

void	ZombieHorde::~ZombieHorde()
{
	delete [] this->zombies;
	this->size = 1;
}

