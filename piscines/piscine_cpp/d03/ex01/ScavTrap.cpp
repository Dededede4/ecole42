#include <iostream>
#include "ScavTrap.hpp"

ScavTrap::ScavTrap(std::string name) : 

	hit_points(100)
	,max_hit_points(100)
	,energy_points(50)
	,max_energy_points(50)
	,level(1)
	,name(name)
	,melee_attack_damage(20)
	,ranged_attack_damage(15)
	,armor_damage_reduction(3)
{
	(void)this->max_energy_points;
	(void)this->level;
}

ScavTrap::ScavTrap(ScavTrap const & src) {
	*this = src;
}

ScavTrap::~ScavTrap(void) {

}

ScavTrap & ScavTrap::operator=( ScavTrap const & rhs) {
	if (this != &rhs)
	{
		this->hit_points = rhs.hit_points;
		this->max_hit_points = rhs.max_hit_points;
		this->energy_points = rhs.energy_points;
		this->max_energy_points = rhs.max_energy_points;
		this->level = rhs.level;
		this->name = rhs.name;
		this->melee_attack_damage = rhs.melee_attack_damage;
		this->ranged_attack_damage = rhs.ranged_attack_damage;
		this->armor_damage_reduction = rhs.armor_damage_reduction;
	}
	return *this;
}

void ScavTrap::rangedAttack(std::string const & target)
{
	std::cout << "Claptrap "<< this->name <<" attacks " << target << " at range, causing " << this->ranged_attack_damage << " points of damage !" << std::endl;
}
void ScavTrap::meleeAttack(std::string const & target)
{
	std::cout << "Claptrap "<< this->name <<" attacks " << target << " at melee, causing " << this->melee_attack_damage << " points of damage !" << std::endl;
}
void ScavTrap::takeDamage(unsigned int amount)
{
	if (amount <= (unsigned int)this->armor_damage_reduction)
	{
		std::cout << "Claptrap "<< this->name <<" was attacked but he did not feel anything." << std::endl;	
	}
	else
	{
		this->hit_points -= (amount - this->armor_damage_reduction);
		std::cout << "Claptrap "<< this->name <<" take " << (amount - this->armor_damage_reduction) << " points of damage :/" << std::endl;
		if (this->hit_points <= 0)
		{
			std::cout << "Claptrap "<< this->name <<" IS KO 😵" << std::endl;
			this->hit_points = 0;
		}
	}
}
void ScavTrap::beRepaired(unsigned int amount)
{
	if ((unsigned int)this->energy_points + amount >= (unsigned int)this->max_hit_points)
	{
		this->energy_points = this->max_hit_points;
		std::cout << "Claptrap "<< this->name <<" is completely repaired ! 💖" << std::endl;
	}
	else
	{
		this->energy_points += amount;
		std::cout << "Claptrap "<< this->name <<" be repaired for " << amount << " ! 💖" << std::endl;
	}
}

void ScavTrap::challengeNewcomer(void)
{
	std::string challenges[4] = {"make Cinnamon challenge", "make Charlie Charlie Challenge", "make Ice and Salt Challenge", "make Condom challenge"};
	
	std::cout << "Claptrap "<< this->name << " " << challenges[rand() % 4] << ". 😨" << std::endl;
}