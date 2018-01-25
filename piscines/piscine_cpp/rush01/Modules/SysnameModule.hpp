#ifndef SYSMEMODULE_HPP
# define SYSMEMODULE_HPP

#include "hostname_infos.hpp"
#include "IMonitorModule.hpp"

class SysnameModule : public hostname_infos, IMonitorModule
{
public:
	SysnameModule();
	virtual ~SysnameModule();
	SysnameModule(SysnameModule const & src);
	SysnameModule & operator=(SysnameModule const & rhs);
	
	virtual std::string getValue() const;
};

#endif