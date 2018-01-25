#ifndef ZOMBIE_HPP
# define ZOMBIE_HPP

# include <string>

class Zombie {
	public:
		Zombie(std::string name, std::string type);
		void announce() const;
	private:
		std::string type;
		std::string name;
};
#endif