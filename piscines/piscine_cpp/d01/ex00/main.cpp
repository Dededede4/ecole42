#include "Pony.hpp"

#include <iostream>

void	ponyOnTheHeap()
{
	Pony 	*pony = new Pony;

	std::cout << "ponyOnTheHeap content" << std::endl;

	delete pony;
}

void	ponyOnTheStack()
{
	Pony 	pony;

	std::cout << "ponyOnTheStack content" << std::endl;
}

int		main()
{
	ponyOnTheHeap();
	ponyOnTheStack();
	return 0;
}