#ifndef HOSTNAMEMODULE_HPP
# define HOSTNAMEMODULE_HPP

#include "hostname_infos.hpp"
#include "IMonitorModule.hpp"

class HostnameModule :  public hostname_infos, IMonitorModule
{
public:
	HostnameModule();
	virtual ~HostnameModule();
	HostnameModule(HostnameModule const & src);
	HostnameModule & operator=(HostnameModule const & rhs);

	std::string getValue() const;
};

#endif