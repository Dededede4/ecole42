#include "DateTimeModule.hpp"

std::string DateTimeModule::getValue() const
{
	QDateTime	time = QDateTime::currentDateTime();
	QString	text = time.toString("dd.MM.yyyy hh:mm");

	return text.toStdString();
}

DateTimeModule::DateTimeModule(){}
DateTimeModule::~DateTimeModule(){}

DateTimeModule::DateTimeModule(DateTimeModule const & src)
{
	*this = src;
	return;
}

DateTimeModule & DateTimeModule::operator=(DateTimeModule const & rhs)
{
	static_cast<void>(rhs);
	return *this;
}
