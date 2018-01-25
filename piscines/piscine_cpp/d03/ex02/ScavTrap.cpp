#include <iostream>
#include "ClapTrap.hpp"
#include "ScavTrap.hpp"

ScavTrap::ScavTrap(std::string name) : ClapTrap(name)
{

	hit_points = 100;
	max_hit_points = 100;
	energy_points = 50;
	max_energy_points = 50;
	level = 1;
	name = name;
	melee_attack_damage = 20;
	ranged_attack_damage = 15;
	armor_damage_reduction = 3;
	childname = "Scav";

}

void ScavTrap::challengeNewcomer(void)
{
	std::string challenges[4] = {"make Cinnamon challenge", "make Charlie Charlie Challenge", "make Ice and Salt Challenge", "make Condom challenge"};
	
	std::cout << "Scav "<< this->name << " " << challenges[rand() % 4] << ". 😨" << std::endl;
}

ScavTrap::~ScavTrap(void) {
	std::cout << "DESTRUTION MESSAGE" << std::endl;
	ClapTrap::~ClapTrap();
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