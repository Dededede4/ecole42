#ifndef PONEY_DISPLAY_HPP
# define PONEY_DISPLAY_HPP

#include "IMonitorDisplay.hpp"

class PONEY_Display_GUI : public IMonitorDisplay
{
	public :
		PONEY_Display_GUI();
		PONEY_Display_GUI(PONEY_Display_GUI const & src);
		virtual ~PONEY_Display_GUI(void);
		PONEY_Display_GUI & operator=( PONEY_Display_GUI const & rhs);

		virtual QWidget * initGUI(void);

		virtual void		update(void);
	private :
};

class PONEY_Display_CLI : public IMonitorDisplay
{
	public :
		PONEY_Display_CLI();
		PONEY_Display_CLI(PONEY_Display_CLI const & src);
		virtual ~PONEY_Display_CLI(void);
		PONEY_Display_CLI & operator=( PONEY_Display_CLI const & rhs);

		virtual void		update(void);

		virtual std::string cliUI();
	private :
};

#endif