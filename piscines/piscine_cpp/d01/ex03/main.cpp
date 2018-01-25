#include "ZombieHorde.hpp"
#include "Zombie.hpp"

#include <iostream>
#include <time.h> 

int			main(void)
{
	srand(time(NULL));
	
	std::cout << "On lâche les zonzons" << std::endl;

	ZombieHorde zo(42);

	std::cout << "On les fait crier" << std::endl;

	zo.announce();

	std::cout << "On les tues" << std::endl;

	zo.release();
}
