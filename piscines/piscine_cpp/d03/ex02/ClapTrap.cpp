#include "ClapTrap.hpp"

ClapTrap::ClapTrap(std::string name) : 

	hit_points(100)
	,max_hit_points(100)
	,energy_points(100)
	,max_energy_points(100)
	,level(1)
	,name(name)
	,melee_attack_damage(30)
	,ranged_attack_damage(20)
	,armor_damage_reduction(5)
	,childname("noname")
{
	std::cout << "CONSTRUCTION MESSAGE" << std::endl;
}

ClapTrap::ClapTrap(ClapTrap const & src) {
	*this = src;
}

ClapTrap::~ClapTrap(void) {
	std::cout << "DESTRUTION MESSAGE" << std::endl;
}

ClapTrap & ClapTrap::operator=( ClapTrap const & rhs) {
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

void ClapTrap::rangedAttack(std::string const & target)
{
	std::cout << this->childname << " "<< this->name <<" attacks " << target << " at range, causing " << this->ranged_attack_damage << " points of damage !" << std::endl;
}
void ClapTrap::meleeAttack(std::string const & target)
{
	std::cout << this->childname << " "<< this->name <<" attacks " << target << " at melee, causing " << this->melee_attack_damage << " points of damage !" << std::endl;
}
void ClapTrap::takeDamage(unsigned int amount)
{
	if (amount <= (unsigned int)this->armor_damage_reduction)
	{
		std::cout << this->childname << " "<< this->name <<" was attacked but he did not feel anything." << std::endl;	
	}
	else
	{
		this->hit_points -= (amount - this->armor_damage_reduction);
		std::cout << this->childname << " "<< this->name <<" take " << (amount - this->armor_damage_reduction) << " points of damage :/" << std::endl;
		if (this->hit_points <= 0)
		{
			std::cout << this->childname << " "<< this->name <<" IS KO 😵" << std::endl;
			this->hit_points = 0;
		}
	}
}
void ClapTrap::beRepaired(unsigned int amount)
{
	if ((unsigned int)this->energy_points + amount >= (unsigned int)this->max_hit_points)
	{
		this->energy_points = this->max_hit_points;
		std::cout << this->childname << " "<< this->name <<" is completely repaired ! 💖" << std::endl;
	}
	else
	{
		this->energy_points += amount;
		std::cout << this->childname << " "<< this->name <<" be repaired for " << amount << " ! 💖" << std::endl;
	}
}
