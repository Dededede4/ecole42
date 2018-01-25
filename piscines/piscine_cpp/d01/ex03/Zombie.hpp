#ifndef ZOMBIE_HPP
# define ZOMBIE_HPP

# include <string>

class Zombie {
	public:
		void setName(std::string name);
		void setType(std::string type);
		void announce() const;
		Zombie();
		~Zombie();
	private:
		std::string type;
		std::string name;
};
#endif