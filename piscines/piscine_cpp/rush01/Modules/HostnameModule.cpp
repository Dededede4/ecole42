#include "HostnameModule.hpp"

HostnameModule::HostnameModule(){}
HostnameModule::~HostnameModule(){}

HostnameModule::HostnameModule(HostnameModule const & src)
{
	*this = src;
	return;
}

HostnameModule & HostnameModule::operator=(HostnameModule const & rhs)
{
	static_cast<void>(rhs);
	return *this;
}

std::string HostnameModule::getValue() const {
	std::string ret = this->name.sysname;
	return name.nodename;
}
