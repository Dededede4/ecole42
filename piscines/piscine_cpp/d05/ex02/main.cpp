
#include <iostream>
#include "Bureaucrat.hpp"

#include "Form.hpp"

int	main(void)
{
	// CONST
	// à quoi sert "execute"
	Bureaucrat francois("Francois", 43);

	//Form LaisserPasserA38
	Form FormulaireBleu("FormulaireBleu", 42, 12);
	Form FormulaireRose("FormulaireRose", 44, 12);
	Form FormulaireJaune("FormulaireJaune", 43, 12);
	Form FormulaireVert("FormulaireVert", 5, 12);

	francois.signForm(FormulaireBleu);
	francois.signForm(FormulaireRose);
	francois.signForm(FormulaireJaune);

}