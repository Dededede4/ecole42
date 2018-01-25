#ifndef IMONITOR_MODULE_HPP
# define IMONITOR_MODULE_HPP

#include <string>

class IMonitorModule {
	public :
		virtual std::string getValue(void) const = 0;
};

#endif