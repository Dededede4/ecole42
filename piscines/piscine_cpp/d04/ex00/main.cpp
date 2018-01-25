#include "Peon.hpp"
#include "Victim.hpp"
#include "Sorcerer.hpp"
#include "Zaz.hpp"

int main()
{
	Sorcerer robert("Robert", "the Magnificent");
	Victim jim("Jimmy");
	Peon joe("Joe");
	std::cout << robert << jim << joe;
	robert.polymorph(jim);
	robert.polymorph(joe);
	Zaz z("Zaz");
	std::cout << z;
	return 0;
}