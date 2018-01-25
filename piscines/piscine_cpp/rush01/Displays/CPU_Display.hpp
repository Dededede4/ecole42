#ifndef CPU_DISPLAY_HPP
# define CPU_DISPLAY_HPP

#include "Displays/IMonitorDisplay.hpp"
#include "Modules/CpuModule.hpp"

class CPU_Display_GUI : public IMonitorDisplay
{
	public :
		CPU_Display_GUI();
		CPU_Display_GUI(CPU_Display_GUI const & src);
		virtual ~CPU_Display_GUI(void);
		CPU_Display_GUI & operator=( CPU_Display_GUI const & rhs);

		virtual QWidget * initGUI(void);

		virtual void		update(void);
	private :
		int				i;
		QSplineSeries	*series;
		QChart			*chart;
};


class CPU_Display_CLI : public IMonitorDisplay
{
	public :
		CPU_Display_CLI();
		CPU_Display_CLI(CPU_Display_CLI const & src);
		virtual ~CPU_Display_CLI(void);
		CPU_Display_CLI & operator=( CPU_Display_CLI const & rhs);

		virtual void		update(void);
		virtual std::string cliUI();
	private :
};

#endif