#ifndef MEMORYMODULE_HPP
# define MEMORYMODULE_HPP

#include <mach/vm_statistics.h>
#include <mach/mach_types.h>
#include <mach/mach_init.h>
#include <mach/mach_host.h>

#include <sys/types.h>
#include <sys/sysctl.h>

#include <iomanip>
#include <iostream>
#include <exception>
#include <string>
#include <sstream>

#include "IMonitorModule.hpp"

class MemoryModule : public IMonitorModule
{
public:
	MemoryModule();
	virtual ~MemoryModule();
	MemoryModule(MemoryModule const & src);
	MemoryModule & operator=(MemoryModule const & rhs);

	virtual std::string getValue(void) const;

	unsigned long long memSizeTotal(void) const;

	unsigned long long memFree(void) const;

	unsigned long long memUsed() const;

private:

};

#endif