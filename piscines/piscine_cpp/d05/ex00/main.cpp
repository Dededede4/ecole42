
#include <iostream>
#include "Bureaucrat.hpp"

int	main(void)
{
	try {
		Bureaucrat francois("Francois", 5000);
	}
	catch (std::exception& e)
	{
		std::cout << "ERROR : " << e.what() << std::endl;
	}

	try {
		Bureaucrat francois2("Francois", 0);
	}
	catch (std::exception& e)
	{
		std::cout << "ERROR : " << e.what() << std::endl;
	}

	Bureaucrat francois3("Francois", 5);
	francois3.incrementGrade();
	francois3.incrementGrade();
	francois3.incrementGrade();
	francois3.incrementGrade();
	try {
		francois3.incrementGrade();
	}
	catch (std::exception& e)
	{
		std::cout << "ERROR : " << e.what() << std::endl;
	}

	Bureaucrat francois4("Francois", 150);
	try {
		francois4.decrementGrade();
	}
	catch (std::exception& e)
	{
		std::cout << "ERROR : " << e.what() << std::endl;
	}

	Bureaucrat francois5("Francois42", 42);
	std::cout << francois5 << std::endl;
	francois5.incrementGrade();
	std::cout << francois5 << std::endl;
	francois5.decrementGrade();
	francois5.decrementGrade();
	std::cout << francois5 << std::endl;

}