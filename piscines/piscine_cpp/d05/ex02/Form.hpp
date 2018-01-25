#ifndef FORM_HPP
# define FORM_HPP

#include <iostream>

class Bureaucrat;

class Form {

public:
	Form(std::string name, int grade_required_to_sign_me, int grade_required_to_execute_me);
	Form(Form const & src);
	virtual ~Form(void);

	Form & operator=( Form const & rhs);


	std::string getName() const;
	int getGrade() const;

	void beSigned(Bureaucrat const & bureaucrat);

	class GradeTooLowException : public std::exception {
		public :
			virtual char const * what() const throw();
	};
	class GradeTooHighException : public std::exception {
		public :
			virtual char const * what() const throw();
	};

	bool isSigned() const;
	int getGradeRequiredToSignMe(void) const;
	int getGradeRequiredToExecuteMe(void) const;
private :
	const std::string	name;
	bool signedform;
	const int grade_required_to_sign_me;
	const int grade_required_to_execute_me;

};

std::ostream & operator<<( std::ostream & o, Form const & rhs );

#endif