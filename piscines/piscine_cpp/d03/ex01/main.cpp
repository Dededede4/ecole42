#include <iostream>
#include "FragTrap.hpp"
#include "ScavTrap.hpp"

int main(void)
{
	srand(time(NULL));

	FragTrap ft("R2D2");

	ft.rangedAttack("Trump2");
	ft.rangedAttack("Trump3");
	ft.rangedAttack("Trump4");
	ft.rangedAttack("Trump5");

	ft.takeDamage(10);
	ft.takeDamage(30);
	ft.takeDamage(20);
	ft.takeDamage(50);
	ft.takeDamage(50);

	ft.beRepaired(111000);

	ft.takeDamage(10);
	ft.takeDamage(30);
	ft.takeDamage(20);
	ft.takeDamage(50);
	ft.takeDamage(50);

	ft.beRepaired(111000);

	ft.meleeAttack("Milie");

	ft.vaulthunter_dot_exe("Bush");
	ft.vaulthunter_dot_exe("Bush");
	ft.vaulthunter_dot_exe("Bush");
	ft.vaulthunter_dot_exe("Bush");
	ft.vaulthunter_dot_exe("Bush");

	std::cout << "Test copy : " << std::endl;
	FragTrap test("test");
	test = ft;
	test.vaulthunter_dot_exe("Bush");


	ScavTrap kevin("KevinDu68");

	kevin.rangedAttack("Trump2");
	kevin.rangedAttack("Trump3");
	kevin.rangedAttack("Trump4");
	kevin.rangedAttack("Trump5");

	kevin.takeDamage(10);
	kevin.takeDamage(30);
	kevin.takeDamage(20);
	kevin.takeDamage(50);
	kevin.takeDamage(50);

	kevin.beRepaired(111000);

	kevin.takeDamage(10);
	kevin.takeDamage(30);
	kevin.takeDamage(20);
	kevin.takeDamage(50);
	kevin.takeDamage(50);

	kevin.beRepaired(111000);

	kevin.meleeAttack("Milie");

	kevin.challengeNewcomer();
	kevin.challengeNewcomer();
	kevin.challengeNewcomer();
	kevin.challengeNewcomer();
	kevin.challengeNewcomer();

	std::cout << "Test copy : " << std::endl;
	ScavTrap test2("test2");
	test2 = kevin;
	test2.challengeNewcomer();

}