#include <iostream>
#include "FragTrap.hpp"


FragTrap::FragTrap(std::string name) : ClapTrap(name)
{
	hit_points = 100;
	max_hit_points = 100;
	energy_points = 100;
	max_energy_points = 100;
	level = 1;
	name = name;
	melee_attack_damage = 30;
	ranged_attack_damage = 20;
	armor_damage_reduction = 5;
	childname = "FR4G-TP";
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

FragTrap::~FragTrap(void) {
	std::cout << "DESTRUTION MESSAGE CHILD" << std::endl;
	ClapTrap::~ClapTrap();
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