#ifndef BUREAUCRAT_HPP
# define BUREAUCRAT_HPP

#include <iostream>
#include "Form.hpp"

class Form;

class Bureaucrat {

public:
	Bureaucrat(std::string name, int grade);
	Bureaucrat(Bureaucrat const & src);
	virtual ~Bureaucrat(void);

	Bureaucrat & operator=( Bureaucrat const & rhs);


	std::string getName() const;
	int getGrade() const;

	void incrementGrade();
	void decrementGrade();
	void signForm(Form & form);

	class GradeTooLowException : public std::exception {
		public :
			virtual char const * what() const throw();
	};
	class GradeTooHighException : public std::exception {
		public :
			virtual char const * what() const throw();
	};
private :
	std::string	name;
	int grade;
};

std::ostream & operator<<( std::ostream & o, Bureaucrat const & rhs );

#endif