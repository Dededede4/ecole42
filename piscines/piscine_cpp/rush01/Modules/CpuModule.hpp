#ifndef CPUMODULE_HPP
# define CPUMODULE_HPP

#include <stdio.h>
#include <cstdio>
#include <iostream>
#include <memory>
#include <stdexcept>
#include <string>
#include <array>

#include "IMonitorModule.hpp"

class CpuModule : public IMonitorModule
{
public:
	CpuModule();
	virtual ~CpuModule();
	CpuModule(CpuModule const & src);
	CpuModule & operator=(CpuModule const & rhs);

	virtual std::string getValue() const;

	std::string getModel() const;

	std::string getNbrCore() const;
};

#endif
