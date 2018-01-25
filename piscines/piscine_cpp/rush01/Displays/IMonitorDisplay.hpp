#ifndef IMONITOR_DISPLAY_HPP
# define IMONITOR_DISPLAY_HPP

#include <QApplication>
#include <QPushButton>
#include <QtCharts>

class IMonitorDisplay {
	public :
		virtual void		update(void) = 0;
};

#endif