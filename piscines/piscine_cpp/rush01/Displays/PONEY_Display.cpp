#include "PONEY_Display.hpp"

PONEY_Display_GUI::PONEY_Display_GUI(void){}
PONEY_Display_GUI::~PONEY_Display_GUI(void){}
PONEY_Display_GUI & PONEY_Display_GUI::operator=( PONEY_Display_GUI const & rhs) 
{
    (void)rhs;
    return *this;
}
PONEY_Display_GUI::PONEY_Display_GUI(PONEY_Display_GUI const & src)
{
    *this = src;
}

QWidget * PONEY_Display_GUI::initGUI(void)
{
	QMovie *movie = new QMovie("giphy.gif");
	QLabel *processLabel = new QLabel();

	processLabel->setMovie(movie);
	movie->start();

	return processLabel;
}

void		PONEY_Display_GUI::update(void)
{
}


void		PONEY_Display_CLI::update(void)
{
}

std::string PONEY_Display_CLI::cliUI()
{
	if ((rand() % 2 & 1)) {
		return
	"         -~~,\n"
	"  ,; _ _~ |\\|\n"
	" ;; ( )_, )\n"
	" ;; /|  |.\\\n"
	;
	} else {
		return
	"         _,_\n"
	"        ;'._\\\n"
	"       ';) \\._,\n"
	"        /  /`-'\n"
	"     ~~( )/\n"
	"        )))\n"
	"        \\\\\\\n"
	;
	}
}

PONEY_Display_CLI::PONEY_Display_CLI(void){}
PONEY_Display_CLI::~PONEY_Display_CLI(void){}
PONEY_Display_CLI & PONEY_Display_CLI::operator=( PONEY_Display_CLI const & rhs) 
{
    (void)rhs;
    return *this;
}
PONEY_Display_CLI::PONEY_Display_CLI(PONEY_Display_CLI const & src)
{
    *this = src;
}