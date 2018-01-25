#include <iostream>
#include "Array.hpp"

int main(void)
{
	Array<int> tab(50);
	tab[5] = 42;
	std::cout << tab[5] << std::endl;
	std::cout << tab.size() << std::endl;
	try {
		tab[500];
	}
	catch(std::exception& e) {
		std::cout << "Error" << std::endl;
	}
	return (0);
}