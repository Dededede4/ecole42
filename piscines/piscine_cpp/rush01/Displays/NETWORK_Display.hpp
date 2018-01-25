#ifndef NETWORK_DISPLAY_HPP
# define NETWORK_DISPLAY_HPP

#include "IMonitorDisplay.hpp"
#include "Modules/NetworkModule.hpp"

class NETWORK_Display_GUI : public IMonitorDisplay
{
	public :
		NETWORK_Display_GUI();
		NETWORK_Display_GUI(NETWORK_Display_GUI const & src);
		virtual ~NETWORK_Display_GUI(void);
		NETWORK_Display_GUI & operator=( NETWORK_Display_GUI const & rhs);

		virtual QWidget * initGUI(void);

		virtual void		update(void);
	private :
		unsigned long long	nbrpaquets;
		unsigned int i;
		QSplineSeries	*series;
		QChart			*chart;
};

class NETWORK_Display_CLI : public IMonitorDisplay
{
	public :
		NETWORK_Display_CLI();
		NETWORK_Display_CLI(NETWORK_Display_CLI const & src);
		virtual ~NETWORK_Display_CLI(void);
		NETWORK_Display_CLI & operator=( NETWORK_Display_CLI const & rhs);

		virtual void		update(void);
		virtual std::string cliUI();
	private :
};

#endif