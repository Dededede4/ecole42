#include <iostream>
#include "FragTrap.hpp"

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

}