#ifndef CLAP_TRAP_HPP
# define CLAP_TRAP_HPP

#include <iostream>

class ClapTrap {

public:
	ClapTrap(std::string name);
	ClapTrap(ClapTrap const & src);
	~ClapTrap(void);

	ClapTrap & operator=( ClapTrap const & rhs);

	void rangedAttack(std::string const & target);
	void meleeAttack(std::string const & target);
	void takeDamage(unsigned int amount);
	void beRepaired(unsigned int amount);

protected :
	int	hit_points;
	int max_hit_points;
	int energy_points;
	int max_energy_points;
	int level;
	std::string name;
	int melee_attack_damage;
	int ranged_attack_damage;
	int armor_damage_reduction;
	std::string childname;


};

#endif