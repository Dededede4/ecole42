#ifndef FRAG_TRAP_HPP
# define FRAG_TRAP_HPP
#include "ClapTrap.hpp"
#include <iostream>

class FragTrap : public ClapTrap{

public:
	FragTrap(std::string name);
	FragTrap(FragTrap const & src);
	~FragTrap(void);

	FragTrap & operator=( FragTrap const & rhs);

	void vaulthunter_dot_exe(std::string const & target);
};

#endif