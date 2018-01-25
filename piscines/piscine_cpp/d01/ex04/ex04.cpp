#include <iostream>

int		main(void)
{
	std::string str = "HI THIS IS BRAIN";

	std::string *a = &str;
	std::string &b = str;

	std::cout << *a << std::endl << b << std::endl;

	return (0);
}
