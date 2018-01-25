#include "ZombieEvent.hpp"
#include "Zombie.hpp"

#include <iostream>
#include <time.h> 

int			main(void)
{
	srand(time(NULL));
	
	ZombieEvent *ze = new ZombieEvent();

	ze->setZombieType("Capitalist");
	Zombie *a = ze->randomChump();
	a->announce();

	Zombie *b = ze->randomChump();
	b->announce();

	ze->setZombieType("Communist");
	Zombie *c = ze->randomChump();
	c->announce();


	delete a;
	delete b;
	delete c;
	delete ze;
}