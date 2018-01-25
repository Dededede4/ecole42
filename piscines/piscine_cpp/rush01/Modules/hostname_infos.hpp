#ifndef HOSTNAME_INFOS_HPP
# define HOSTNAME_INFOS_HPP

#include <sys/utsname.h>
#include <exception>
#include <iostream>

class			hostname_infos
{
	public :
		hostname_infos();
		virtual ~hostname_infos();
		hostname_infos(hostname_infos const & src);
		hostname_infos & operator=(hostname_infos const & rhs);
		struct utsname getSysname() const;
	protected :
		struct utsname	name;
};

#endif