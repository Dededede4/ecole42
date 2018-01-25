#include <iostream>
#include "FragTrap.hpp"

FragTrap::FragTrap(std::string name) : 

	hit_points(100)
	,max_hit_points(100)
	,energy_points(100)
	,max_energy_points(100)
	,level(1)
	,name(name)
	,melee_attack_damage(30)
	,ranged_attack_damage(20)
	,armor_damage_reduction(5)
{
	(void)this->max_energy_points;
	(void)this->level;
}

FragTrap::FragTrap(FragTrap const & src) {
	*this = src;
}

FragTrap::~FragTrap(void) {

}

FragTrap & FragTrap::operator=( FragTrap const & rhs) {
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

void FragTrap::rangedAttack(std::string const & target)
{
	std::cout << "FR4G-TP "<< this->name <<" attacks " << target << " at range, causing " << this->ranged_attack_damage << " points of damage !" << std::endl;
}
void FragTrap::meleeAttack(std::string const & target)
{
	std::cout << "FR4G-TP "<< this->name <<" attacks " << target << " at melee, causing " << this->melee_attack_damage << " points of damage !" << std::endl;
}
void FragTrap::takeDamage(unsigned int amount)
{
	if (amount <= (unsigned int)this->armor_damage_reduction)
	{
		std::cout << "FR4G-TP "<< this->name <<" was attacked but he did not feel anything." << std::endl;	
	}
	else
	{
		this->hit_points -= (amount - this->armor_damage_reduction);
		std::cout << "FR4G-TP "<< this->name <<" take " << (amount - this->armor_damage_reduction) << " points of damage :/" << std::endl;
		if (this->hit_points <= 0)
		{
			std::cout << "FR4G-TP "<< this->name <<" IS KO 😵" << std::endl;
			this->hit_points = 0;
		}
	}
}
void FragTrap::beRepaired(unsigned int amount)
{
	if ((unsigned int)this->energy_points + amount >= (unsigned int)this->max_hit_points)
	{
		this->energy_points = this->max_hit_points;
		std::cout << "FR4G-TP "<< this->name <<" is completely repaired ! 💖" << std::endl;
	}
	else
	{
		this->energy_points += amount;
		std::cout << "FR4G-TP "<< this->name <<" be repaired for " << amount << " ! 💖" << std::endl;
	}
}

void FragTrap::vaulthunter_dot_exe(std::string const & target)
{
	if (this->energy_points < 25)
	{
		std::cout << "FR4G-TP "<< this->name <<" does not have enough energy to make a random attack! 😴" << std::endl;
		return ;
	}
	std::string attacks[5] = {"use a katana", "use a plastic katana", "uses a laser katana", "uses a katana from another dimension", "uses a fused katana to another katana"};
	
	std::cout << "FR4G-TP "<< this->name << " " << attacks[rand() % 4] << " to attack " << target << " ⚔️" << std::endl;

	this->energy_points -= 25;
}