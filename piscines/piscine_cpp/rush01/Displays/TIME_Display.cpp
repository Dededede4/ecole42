#include "TIME_Display.hpp"
#include "Modules/DateTimeModule.hpp"

TIME_Display_GUI::TIME_Display_GUI(void){}
TIME_Display_GUI::~TIME_Display_GUI(void){}
TIME_Display_GUI & TIME_Display_GUI::operator=( TIME_Display_GUI const & rhs) 
{
    (void)rhs;
    return *this;
}
TIME_Display_GUI::TIME_Display_GUI(TIME_Display_GUI const & src)
{
    *this = src;
}

QWidget * TIME_Display_GUI::initGUI(void)
{
	DateTimeModule datetime;

    number = new QLCDNumber();
    number->setDigitCount(16);
    number->setSegmentStyle(QLCDNumber::Flat);
    
    number->display(QString::fromStdString(datetime.getValue()));
    number->setFrameStyle(QFrame::NoFrame);
	return number;
}

void		TIME_Display_GUI::update(void)
{
	DateTimeModule datetime;
    number->display(QString::fromStdString(datetime.getValue()));
}

void		TIME_Display_CLI::update(void)
{
}

std::string	TIME_Display_CLI::cliUI()
{
	DateTimeModule datetime;

	return datetime.getValue();
}

TIME_Display_CLI::TIME_Display_CLI(void){}
TIME_Display_CLI::~TIME_Display_CLI(void){}
TIME_Display_CLI & TIME_Display_CLI::operator=( TIME_Display_CLI const & rhs) 
{
    (void)rhs;
    return *this;
}
TIME_Display_CLI::TIME_Display_CLI(TIME_Display_CLI const & src)
{
    *this = src;
}