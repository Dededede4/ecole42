#include "SysnameModule.hpp"


std::string SysnameModule::getValue() const
{
	std::string ret = this->name.sysname;
	return std::string(name.sysname) + " Kernel Version " + std::string(name.release) + " " + std::string(name.machine);
}

SysnameModule::SysnameModule(){}
SysnameModule::~SysnameModule(){}

SysnameModule::SysnameModule(SysnameModule const & src)
{
	*this = src;
	return;
}

SysnameModule & SysnameModule::operator=(SysnameModule const & rhs)
{
	static_cast<void>(rhs);
	return *this;
}