#ifndef DATETIMEMODULE_HPP
# define DATETIMEMODULE_HPP

#include "IMonitorModule.hpp"

#include <QApplication>
#include <QPushButton>
#include <QtCharts>

class DateTimeModule : public IMonitorModule
{
public:
	DateTimeModule();
	virtual ~DateTimeModule();
	DateTimeModule(DateTimeModule const & src);
	DateTimeModule & operator=(DateTimeModule const & rhs);

	std::string getValue() const;
};

#endif