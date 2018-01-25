#ifndef TIME_DISPLAY_HPP
# define TIME_DISPLAY_HPP

#include "IMonitorDisplay.hpp"
#include "Modules/DateTimeModule.hpp"
#include <time.h>

class TIME_Display_GUI : public IMonitorDisplay
{
	public :
		TIME_Display_GUI();
		TIME_Display_GUI(TIME_Display_GUI const & src);
		virtual ~TIME_Display_GUI(void);
		TIME_Display_GUI & operator=( TIME_Display_GUI const & rhs);

		virtual QWidget * initGUI(void);

		virtual void		update(void);
	private :
		QLCDNumber* number;
};

class TIME_Display_CLI : public IMonitorDisplay
{
	public :
		TIME_Display_CLI();
		TIME_Display_CLI(TIME_Display_CLI const & src);
		virtual ~TIME_Display_CLI(void);
		TIME_Display_CLI & operator=( TIME_Display_CLI const & rhs);

		virtual void		update(void);
		virtual std::string	cliUI();
	private :
};

#endif