#ifndef FRAG_TRAP_HPP
# define FRAG_TRAP_HPP

#include <iostream>

class FragTrap {

public:
	FragTrap(std::string name);
	FragTrap(FragTrap const & src);
	~FragTrap(void);

	FragTrap & operator=( FragTrap const & rhs);

	void rangedAttack(std::string const & target);
	void meleeAttack(std::string const & target);
	void takeDamage(unsigned int amount);
	void beRepaired(unsigned int amount);
	void vaulthunter_dot_exe(std::string const & target);

private :
	int	hit_points;
	int max_hit_points;
	int energy_points;
	int max_energy_points;
	int level;
	std::string name;
	int melee_attack_damage;
	int ranged_attack_damage;
	int armor_damage_reduction;


};

#endif