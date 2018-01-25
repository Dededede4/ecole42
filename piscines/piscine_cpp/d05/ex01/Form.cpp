#include <iostream>
#include "Form.hpp"
#include "Bureaucrat.hpp"

const char * Form::GradeTooLowException::what() const throw()
{
	return ("Grade too low");
}

const char * Form::GradeTooHighException::what() const throw()
{
	return ("Grade too high");
}

Form::Form(std::string name, int grade_required_to_sign_me, int grade_required_to_execute_me) :
	name(name)
	,grade_required_to_sign_me(grade_required_to_sign_me)
	,grade_required_to_execute_me(grade_required_to_execute_me)
{
	if (grade_required_to_sign_me > 150 || grade_required_to_execute_me > 150)
	{
		throw GradeTooLowException();
	}
	if (grade_required_to_sign_me < 1 || grade_required_to_execute_me < 1)
	{
		throw GradeTooHighException();
	} 
}

Form::Form(Form const & src) : 
name(src.getName()),
grade_required_to_sign_me(src.getGradeRequiredToSignMe()),
grade_required_to_execute_me(src.getGradeRequiredToSignMe()) {
	*this = src;
}

Form & Form::operator=( Form const & rhs) {
	(void)rhs;
	/*if (this != &rhs)
	{
		name = rhs.name;
		grade_required_to_sign_me = rhs.grade_required_to_sign_me;
		grade_required_to_execute_me =  rhs.grade_required_to_execute_me;
	}*/
	return *this;
}

std::ostream & operator<<( std::ostream & o, Form const & rhs ) {
	o << "Form name :" << rhs.getName() << std::endl
	<< "Grade Required To Sign Me : " << rhs.getGradeRequiredToSignMe() << std::endl
	<< "Grade Required To Execute Me : " << rhs.getGradeRequiredToExecuteMe() << std::endl
	<< "Signed : " << rhs.isSigned();
	return o;
}

Form::~Form(void) {
}


std::string Form::getName() const {
	return name;
}

int Form::getGradeRequiredToSignMe(void) const {
	return grade_required_to_sign_me;
}

int Form::getGradeRequiredToExecuteMe(void) const {
	return grade_required_to_execute_me;
}

bool Form::isSigned() const
{
	return signedform;
}

void Form::beSigned(Bureaucrat const & bureaucrat) {
	if (bureaucrat.getGrade() < grade_required_to_sign_me)
		throw GradeTooLowException();
	signedform = true;
}