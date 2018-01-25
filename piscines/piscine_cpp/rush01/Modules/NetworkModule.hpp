#ifndef NETWORKMODULE_HPP
# define NETWORKMODULE_HPP

#include <stdio.h>
#include <cstdio>
#include <iostream>
#include <memory>
#include <stdexcept>
#include <string>
#include <array>

#include "IMonitorModule.hpp"

class NetworkModule : public IMonitorModule
{
public:
	NetworkModule();
	virtual ~NetworkModule();
	NetworkModule(NetworkModule const & src);
	NetworkModule & operator=(NetworkModule const & rhs);

	virtual std::string getValue() const ;
};

#endif