#ifndef GENERALINFORMATION_DISPLAY_HPP
# define GENERALINFORMATION_DISPLAY_HPP

#include <unistd.h>

#include "Displays/IMonitorDisplay.hpp"
#include "Modules/SysnameModule.hpp"
#include "Modules/HostnameModule.hpp"

class GENERALINFORMATION_Display_GUI : public IMonitorDisplay
{
	public :
		GENERALINFORMATION_Display_GUI();
		GENERALINFORMATION_Display_GUI(GENERALINFORMATION_Display_GUI const & src);
		virtual ~GENERALINFORMATION_Display_GUI(void);
		GENERALINFORMATION_Display_GUI & operator=( GENERALINFORMATION_Display_GUI const & rhs);

		virtual QWidget * initGUI(void);

		virtual void		update(void);
	private :
};

class GENERALINFORMATION_Display_CLI : public IMonitorDisplay
{
	public :
		GENERALINFORMATION_Display_CLI();
		GENERALINFORMATION_Display_CLI(GENERALINFORMATION_Display_CLI const & src);
		virtual ~GENERALINFORMATION_Display_CLI(void);
		GENERALINFORMATION_Display_CLI & operator=( GENERALINFORMATION_Display_CLI const & rhs);

		virtual void		update(void);

		virtual std::string cliUI();
	private :
};


#endif