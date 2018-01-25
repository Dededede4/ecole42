#ifndef MEMORY_DISPLAY_HPP
# define MEMORY_DISPLAY_HPP

#include <QApplication>
#include <QPushButton>
#include <QtCharts>

#include "IMonitorDisplay.hpp"
#include "Modules/MemoryModule.hpp"

class MEMORY_Display_GUI : public IMonitorDisplay
{
	public :
		MEMORY_Display_GUI();
		MEMORY_Display_GUI(MEMORY_Display_GUI const & src);
		virtual ~MEMORY_Display_GUI(void);
		MEMORY_Display_GUI & operator=( MEMORY_Display_GUI const & rhs);

		virtual QWidget * initGUI(void);

		virtual void		update(void);
	private :
		unsigned long long	nbrpaquets;
		unsigned int i;
		QSplineSeries	*series;
		QChart			*chart;
};

class MEMORY_Display_CLI : public IMonitorDisplay
{
	public :
		MEMORY_Display_CLI();
		MEMORY_Display_CLI(MEMORY_Display_CLI const & src);
		virtual ~MEMORY_Display_CLI(void);
		MEMORY_Display_CLI & operator=( MEMORY_Display_CLI const & rhs);

		virtual void		update(void);
		virtual std::string cliUI();
	private :
};

#endif