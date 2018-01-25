#include <iostream>
#include "Bureaucrat.hpp"

const char * Bureaucrat::GradeTooLowException::what() const throw()
{
	return ("Grade too low");
}

const char * Bureaucrat::GradeTooHighException::what() const throw()
{
	return ("Grade too high");
}

Bureaucrat::Bureaucrat(std::string name, int grade) : 

	name(name)
	,grade(grade)
{
	if (grade > 150)
	{
		throw GradeTooLowException();
	}
	if (grade < 1)
	{
		throw GradeTooHighException();
	} 
}

Bureaucrat::Bureaucrat(Bureaucrat const & src) {
	*this = src;
}

Bureaucrat & Bureaucrat::operator=( Bureaucrat const & rhs) {
	(void)rhs;
	if (this != &rhs)
	{
		this->name = rhs.name;
		this->grade = rhs.grade;
	}
	return *this;
}

std::ostream & operator<<( std::ostream & o, Bureaucrat const & rhs ) {
	o << rhs.getName() << ", bureaucrat grade " << rhs.getGrade();
	return o;
}

Bureaucrat::~Bureaucrat(void) {
}


int Bureaucrat::getGrade() const {
	return grade;
}

std::string Bureaucrat::getName() const {
	return name;
}

void Bureaucrat::incrementGrade() {
	if (grade == 1)
		throw GradeTooHighException();
	grade--;
}

void Bureaucrat::decrementGrade() {
	if (grade == 150)
		throw GradeTooLowException();
	grade++;
}