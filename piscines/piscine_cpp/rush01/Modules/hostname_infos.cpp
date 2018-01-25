#include "hostname_infos.hpp"

hostname_infos::hostname_infos()
{
	try
	{
		int test = uname(&name);
		if (test == -1) {
			throw std::exception();
		}
	}
	catch (std::exception &e)
	{
		std::cerr << e.what() << std::endl;
	}
}
struct utsname hostname_infos::getSysname() const
{
	return name;
}

hostname_infos::~hostname_infos(){}

hostname_infos::hostname_infos(hostname_infos const & src)
{
	*this = src;
	return;
}

hostname_infos & hostname_infos::operator=(hostname_infos const & rhs)
{
	if (this != &rhs) {
		this->name = rhs.getSysname();
	}
	return *this;
}
